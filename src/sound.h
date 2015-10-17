/*
Copyright © Nico Zink
All rights reserved.
*/

#ifndef SOUND_H
#define SOUND_H

// Local Includes

// Project Includes

// External Includes
#include <stdint.h>

// Required classes
class SystemState;

// A class checks the system state and plays the sound.
class Sound
{
  public:
  
    Sound();
    ~Sound();

    void GenerateSamples(uint8_t *stream, int length);
    void Update(SystemState& state);

  private:

    int beep_samples_left;
    int beep_current_v;
};

#endif

