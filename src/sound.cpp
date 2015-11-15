/*
Copyright © Nico Zink
All rights reserved.
*/

#include "sound.h" 

// Local Includes
#include "system.h"
#include "system_state.h"

// Project Includes

// External Includes
#include <SDL/SDL.h>
#include <SDL/SDL_audio.h>
#include <cmath>

constexpr int AMPLITUDE = 28000;
constexpr int FREQUENCY = 44100;
constexpr int BEEP_HZ = 440;
constexpr double PI = 3.14159265358979323846;

void fill_audio(void *udata, Uint8 *stream, int length)
{
  Sound* sound = (Sound*)udata;

  sound->GenerateSamples((int16_t*)stream, length / 2);
}

Sound::Sound()
{
  SDL_Init(SDL_INIT_AUDIO);

  SDL_AudioSpec desiredSpec;

  desiredSpec.freq = FREQUENCY;
  desiredSpec.format = AUDIO_S16SYS;
  desiredSpec.channels = 1;
  desiredSpec.samples = 2048;
  desiredSpec.callback = fill_audio;
  desiredSpec.userdata = this;

  SDL_AudioSpec obtainedSpec;

  // you might want to look for errors here
  SDL_OpenAudio(&desiredSpec, &obtainedSpec);

  beep_samples_left = 0;

  SDL_PauseAudio(0);
}

Sound::~Sound()
{
  SDL_CloseAudio();
}

void Sound::GenerateSamples(int16_t *stream, int length)
{
  int i = 0;

  int samples_to_generate = std::min(beep_samples_left, length);

  while (i < samples_to_generate) {
    stream[i] = AMPLITUDE * std::sin(beep_current_v * 2 * PI / FREQUENCY);
    beep_current_v += BEEP_HZ;

    i++;
  }

  beep_samples_left -= samples_to_generate;

  while (i < length) {
    stream[i] = 0;

    i++;
  }
}

void Sound::Update(SystemState& state)
{
  if (state.sound_timer != 0)
  {
    SDL_LockAudio();
    
    beep_samples_left = (state.sound_timer * 1000.0 / Globals::TIMER_FREQUENCY) * FREQUENCY / 1000;
    beep_current_v = 0;

    SDL_UnlockAudio();

    state.sound_timer = 0;
  }
}
