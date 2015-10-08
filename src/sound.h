/*
Copyright © Nico Zink
All rights reserved.
*/

#ifndef SOUND_H
#define SOUND_H

// Local Includes

// Project Includes

// External Includes

// Required classes
class SystemState;

// A class checks the system state and plays the sound.
class Sound
{
  public:
  
    Sound();
    ~Sound();

    void Update(SystemState& state);
};

#endif

