#!/bin/sh
# Copy the sound samples the port uses out of the arcade data (read only) into
# data/sound (the BGM is prepare_bgm.sh's).
set -e
cd "$(dirname "$0")"
SRC="../Wangan Midnight Maximum Tune 3DX+ (Japan)/data/sound"
mkdir -p data/sound/engine
# every car's engine and muffler loops (src/sounddb.h names the ones each car type uses)
cp "$SRC"/engine/*.wav data/sound/engine/
for f in slip wall crash1 crash4 valb1 valb2 valb3 gyap phone2; do cp "$SRC/race_se/$f.wav" data/sound/; done
for f in cursor select cancel gamestart ti_count ti_count2 turning6 finish1 turning turning2 turning3 start321 start_go finish2 cutin2 tuning_bar result2 result_pass approach2 approach3 turning3_cutin door_open door_close engine_start rybal_intro parts_equip tuning levelup jack_up jack_down tuning1 tuning2 parts_comp rank win win_bigstar; do cp "$SRC/system_se/$f.wav" data/sound/; done
chmod 644 data/sound/*.wav data/sound/engine/*.wav
ls -l data/sound
