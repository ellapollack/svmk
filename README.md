**SVMK** is a terminal-based virtual MIDI keyboard for [SOUL Patches](https://github.com/soul-lang/SOUL/blob/master/docs/SOUL_Patch_Format.md).
- Supports **hot-reloading** of SOUL Patches (just re-save the patch file)
- Playback is **monophonic** because ANSI terminals don't support keyup events

![](ss.png)

1. Install the latest version of [CMake](https://cmake.org/install/)
2. Download the [`SOUL_PatchLoader DLL`](https://github.com/soul-lang/SOUL/releases/latest) and put it in your [`userApplicationDataDirectory`](https://docs.juce.com/master/classFile.html#a3e19cafabb03c5838160263a6e76313da0c9f89d8dc9f9f32c9eb42428385351d)
4. Download **SVMK**: `git clone --recurse-submodules https://github.com/maxwellpollack/svmk.git && cd svmk`
5. Configure: `cmake .`
6. Build: `cmake --build ./`
7. Run an example patch: `./svmk_artifacts/svmk SOUL/examples/patches/SineSynth/SineSynth.soulpatch`
