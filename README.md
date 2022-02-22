**SVMK** a terminal-based virtual MIDI keyboard for [SOUL Patches](https://github.com/soul-lang/SOUL/blob/master/docs/SOUL_Patch_Format.md) host.

## Installation

1. Download + install the latest version of [CMake](https://cmake.org/install/)
2. Download the [`SOUL_PatchLoader DLL`](https://github.com/soul-lang/SOUL/releases/latest) and place it in the `SOUL` subdirectory of your [`userApplicationDataDirectory`](https://docs.juce.com/master/classFile.html#a3e19cafabb03c5838160263a6e76313da0c9f89d8dc9f9f32c9eb42428385351d)
3. Run these commands to download, build, and run `ego` with a basic sine wave synth:

```
git clone --recurse-submodules https://github.com/maxwellpollack/ego.git
cd ego
cmake .
cmake --build ./
./ego_artefacts/ego SOUL/examples/patches/SineSynth/SineSynth.soulpatch
```