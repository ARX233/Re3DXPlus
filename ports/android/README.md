# Android port source snapshot

This is a development snapshot, not a ready-to-build or tested release. The MIT license covers the port source only; game material is not included or licensed by it. Obtain and use any required game inputs only with appropriate rights, locally and privately. Do not commit generated resources, archives, keys, save files or build output. The local ignore rules are a safety aid, not a substitute for reviewing staged changes.

## Build status and prerequisites

Android SDK (build-tools and platform), NDK, JDK, Python 3 and tools required by the asset generators are needed; some generators need Pillow, capstone, unicorn and c++filt. `build_android.sh` requires explicit `ANDROID_HOME`, `JAVA_HOME`, `SIGNING_KEYSTORE`, `APP_ICON`, and `CARD_RESOURCES`. Signing passwords are requested interactively by apksigner. The script never installs or transfers to a device.

**The source snapshot is incomplete for compilation.** Generated game-derived headers, `src/phys/phys_rc.c` and data files are deliberately absent. The generic generator script requires an explicit original root but intentionally stops before writing because `tools/weartexts.py`, `tools/titledb.py` and the physics roots list are excluded: they contain or may contain original-derived data. The remaining generators alone have not been verified to recreate every missing file. Newer meter, story cut-in and racing lamp inputs require separate local preparation; no complete generation procedure has been validated. `tools/time_texture.py` can generate the time texture header from a user-supplied 64×32 PNG; the image itself is not included. The Vulkan source directory includes 31 public baseline shaders and two derived from this project's SSAO/blur sources; `src/vkgl_spv.c` is generated locally by `tools/vkglsl.py` during the build. Do not upload generated outputs.

Once these gaps are addressed locally, run `./build_android.sh` with the explicit inputs above; `VK=0` selects the GLES path. This is a description of the intended process, not a claim the build succeeds. No actual device testing was performed in this preparation.
