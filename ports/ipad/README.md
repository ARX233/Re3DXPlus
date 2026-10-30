# iPad / iOS port snapshot

This directory contains the iPad development source snapshot, including the iOS host, rendering, graphics-quality and touch/key-layout implementation, plus selected tests and asset-generation tools. It is not a ready-to-build or redistributable game package. The MIT license is in [LICENSE](LICENSE).

## Game data and generated inputs

No game assets, original binaries, packaged media, extracted tables, save files or device credentials are included. Users must independently and lawfully obtain their own compatible game data; this repository does not provide or download it. `tools/gen_from_original.sh` describes one historical generation pipeline and takes an original-data directory. It writes derived files locally and does not supply the original data. It cannot run to completion as shipped: `tools/titledb.py`, `tools/weartexts.py`, and `tools/recomp/roots.txt` are omitted because they contain derived game material. Do not commit or publish those outputs.

Known omitted headers and outputs include `cardb.h`, `carwheel.h`, `dressdb.h`, `meterdb.h`, `meterdb_v2.h`, `neondb.h`, `namedb.h`, `rivaldb.h`, `sounddb.h`, `sparkdb.h`, `titledb.h`, `battle.h`, `tenline.h`, `minicourse.h`, the generated `story*.h`, `sttune.h`, `steff.h`, `tendb.h` tables, `racing_lamp_data.h`, `story_cutin_data.h`, `time_texture.h`, `phys/phys_rc.c`, and derived JSON/text lists and runtime data. Some additional generators are supplied, but not every omitted input is covered by that historical pipeline: in particular, reproduction of the v2 meter table remains unresolved. `tools/time_texture.py` can produce the time texture header from a user-supplied 64×32 PNG, but it does not provide the image. Full data preparation and a clean build have not been verified.

## Build and tests

The previous iPad packaging workflow depended on a particular Mac, prevalidated assets and an existing IPA. Those private scripts are intentionally not included. For a compile-only workflow, see [tools/BUILD_IOS.md](tools/BUILD_IOS.md) and `tools/build_ios.sh`; it requires the excluded inputs to be restored locally. No general-purpose signing, packaging or installation procedure is claimed here. A developer must provide an appropriate Apple toolchain and signing setup independently. Nothing here is configured to upload credentials or assets.

Tests under `test/` are source-level or host-side tests; some require missing generated inputs, platform SDKs or additional tooling. They do not establish full runtime correctness. An isolated copy compiled and linked after private generated inputs were supplied; a clean-clone build, full-data test run and real-device validation remain unverified.
