**SVMK** is a terminal-based virtual MIDI keyboard for [SOUL Patches](https://github.com/soul-lang/SOUL/blob/master/docs/SOUL_Patch_Format.md).
- Supports **hot-reloading** of SOUL Patches (just re-save the patch file)
- Playback is **monophonic** because ANSI terminals don't support keyup events
- Press <kbd>ESC</kbd> to exit

![](ss.png)

1. Download [`svmk`](https://github.com/maxwellpollack/svmk/releases/latest) and put it somewhere in your [`PATH`](https://en.wikipedia.org/wiki/PATH_(variable))
2. Download the [`SOUL_PatchLoader DLL`](https://github.com/soul-lang/SOUL/releases/latest) and put it in a folder called `SOUL` inside your [`userApplicationDataDirectory`](https://docs.juce.com/master/classFile.html#a3e19cafabb03c5838160263a6e76313da0c9f89d8dc9f9f32c9eb42428385351d)
7. Run a patch: `svmk path/to/patchfile.soulpatch`
