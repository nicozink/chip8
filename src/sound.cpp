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

Sound::Sound()
{
  SDL_Init(SDL_INIT_AUDIO);

  SDL_AudioSpec desiredSpec;

  desiredSpec.freq = 44100;
  desiredSpec.format = AUDIO_S16SYS;
  desiredSpec.channels = 1;
  desiredSpec.samples = 2048;
  //desiredSpec.callback = audio_callback;
  //desiredSpec.userdata = this;

  SDL_AudioSpec obtainedSpec;

  // you might want to look for errors here
  SDL_OpenAudio(&desiredSpec, &obtainedSpec);
}

Sound::~Sound()
{
  SDL_CloseAudio();
}

void Sound::Update(SystemState& state)
{
  if (state.play_sound)
  {
    state.play_sound = false;
  }
}
