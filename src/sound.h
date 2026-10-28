/* Software mixer for engine and effect sounds, driven from the arcade's own
 * sample sets and rpm tables. Platform glue (audio output, BGM) lives in
 * sound_ios.m; this file is plain C so it can be tested on the desktop. */
#ifndef SOUND_H
#define SOUND_H

#include "car.h"

#define SND_RATE 44100

/* Loads the WAVs in data_dir/sound (every car's engine sounds in sound/engine). Returns 0
 * on success; missing files are silent. */
int snd_init(const char *data_dir);
/* The engine sound set of the car to drive (its ECarType, car_spec.type) at its power tune
 * (car_spec.power): the arcade's tuned set from power 8 on, below that the stock one. */
void snd_set_car(unsigned type, int power);
/* Game thread, once per frame: turn the car state into voice parameters. */
void snd_update(car_state *car, const car_input *in, float dt);
/* Front-end sounds from the arcade's system_se (SND_START: gamestart.wav, SE 0x3f that
 * clPlayCheckThread plays when the player starts from the attract), and the time attack's:
 * clTimeConsole::setRemainTime ticks each second from 9 left (ti_count, SE 0xf) and from 4
 * (ti_count2, 0x31); a checkpoint's TIME EXTEND (turning6, 0x3b); clTaResult's finish1 (0x24); the
 * route signs' (clSignConsole) turning (0x54), turning2 (0x55) and turning3 (0x56); the start's
 * countdown (clCountDownConsole::setCountDown): start321 (0xc) at 2 and 1, start_go (0xd) at GO;
 * clTaResult's finish2 (0x25) and cutin2 (0x22, each row of the result); the story result's
 * points gauge counting (tuning_bar, 0x43: snd_menu_loop); the 10-in-a-row result's
 * (clTenResult2) result2 (0x29) as a face is crossed out and result_pass (0x36) with the medal; the
 * 10-in-a-row's approach2 (0x4d) as each rival comes on, approach3 (0x4e) for the last
 * (clRaceThread::race, changeTenRival), a rival's line coming up (clCutinDisp::update,
 * turning3_cutin, 0x53) and cutin2 louder as one is beaten (clRaceThread::race, 0x4c). */
enum { SND_CURSOR, SND_SELECT, SND_CANCEL, SND_START, SND_TIME_COUNT, SND_TIME_COUNT_LAST, SND_TIME_EXTEND, SND_FINISH,
       SND_TURN, SND_TURN2, SND_TURN3, SND_START321, SND_START_GO, SND_FINISH2, SND_CUTIN2, SND_TUNING_BAR,
       SND_RESULT2, SND_RESULT_PASS, SND_APPROACH2, SND_APPROACH3, SND_TURN3_CUTIN, SND_BEATEN };
void snd_menu(int which);
/* A one-shot by its file's name (data/sound/<wav>.wav, one of sound.c's) at nsAudio's volume
 * (the one-shot table's: 1 the front end's usual): the story movies' shows' sounds, the dress-up
 * part worn's parts_equip and tuning, the class-up's levelup */
void snd_effect(const char *wav, float vol);
/* A looped front-end sound (SND_TUNING_BAR) on from its start, or off. */
void snd_menu_loop(int which, int on);
/* Silence the car (engine, tyres, wall) when the race is left. */
void snd_quiet(void);
/* Audio thread: mix `frames` interleaved stereo int16 frames. */
void snd_mix(short *out, int frames);

#endif
