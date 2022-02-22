#include "JuceHeader.h"
#include "SOUL/include/soul/patch/helper_classes/soul_patch_AudioProcessor.h"
#include "SOUL/include/soul/patch/helper_classes/soul_patch_CompilerCacheFolder.h"
#include "SOUL/include/soul/patch/helper_classes/soul_patch_LoaderPlugin.h"
#include "UIThread.h"

//==============================================================================
struct SVMK  : public juce::JUCEApplication
{
    SVMK()
    {}

    const juce::String getApplicationName() override       { return ProjectInfo::projectName; }
    const juce::String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override             { return true; }

    void initialise (const juce::String& commandLineParameters) override {

        if (commandLineParameters.isEmpty())
        {
            quit();
            return;
        }

        constexpr uint32_t maxNumCacheFiles = 200;

        #if JUCE_MAC
        auto tempFolder = juce::File ("~/Library/Caches");
        #else
        auto tempFolder = juce::File::getSpecialLocation (juce::File::SpecialLocationType::tempDirectory);
        #endif

        auto cacheFolder = tempFolder.getChildFile ("dev.soul.SOULPlugin").getChildFile ("Cache");

        if (cacheFolder.createDirectory())
            compilerCache = soul::patch::CompilerCache::Ptr (new soul::patch::CompilerCacheFolder (cacheFolder, maxNumCacheFiles));

        // SOULPatchLibrary
        DBG("Library: " << library.getErrorMessage());

        // SOULPatchInstance
        auto patchFile = juce::File::getCurrentWorkingDirectory()
                    .getChildFile(commandLineParameters)
                    .getFullPathName().toStdString();
        DBG("PatchFile exists: " << (juce::File::getCurrentWorkingDirectory()
                    .getChildFile(commandLineParameters)
                    .exists() ? "Exists" : "Dont exists"));

        // SOULPatchAudioProcessor
        processor = std::make_unique<soul::patch::SOULPatchAudioProcessor>
                        (library.createPatchInstance(patchFile),
                         compilerCache);
        processor->askHostToReinitialise = [&]
        {
            player.setProcessor(nullptr);
            processor->reinitialise();
            player.setProcessor(processor.get());
        };

        processor->askHostToReinitialise();

        deviceManager.addAudioCallback (&player);
        deviceManager.addMidiInputDeviceCallback ({}, &player);
        deviceManager.initialiseWithDefaultDevices (2,2);
        // auto defaultSetup = deviceManager.getAudioDeviceSetup();
        // defaultSetup.outputDeviceName = "BlackHole 2ch";
        // deviceManager.setAudioDeviceSetup(defaultSetup, true);

        uiThread = std::make_unique<UIThread>("UI Thread", processor.get());
    }

    void shutdown() override { 
        player.setProcessor(nullptr);
        deviceManager.closeAudioDevice();
    }

    void systemRequestedQuit() override                         { quit(); }
    void anotherInstanceStarted (const juce::String&) override  {}

    // SOUL classes
    soul::patch::PatchLibraryDLL library;
    soul::patch::CompilerCache::Ptr compilerCache;
    std::unique_ptr<soul::patch::SOULPatchAudioProcessor> processor;

    juce::AudioProcessorPlayer player;
    juce::AudioDeviceManager deviceManager;
    std::unique_ptr<UIThread> uiThread;
};

//==============================================================================
START_JUCE_APPLICATION (SVMK)
