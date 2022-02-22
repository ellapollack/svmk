#include "JuceHeader.h"
#include "SOUL/include/soul/patch/helper_classes/soul_patch_AudioProcessor.h"

struct UIThread : juce::Thread {

    UIThread(const char* threadName,
             soul::patch::SOULPatchAudioProcessor* patch);

    ~UIThread();

    void run() override;

    soul::patch::SOULPatchAudioProcessor* patch;
};