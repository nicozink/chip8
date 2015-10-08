/*
Copyright © Nico Zink
All rights reserved.
*/

#ifndef TIMERS_H
#define TIMERS_H

// Local Includes

// Project Includes

// External Includes

// Required classes
class SystemState;

// A class which decrements the sound and delay timers.
class Timers
{
  public:
  
    Timers();
    
    void Count(SystemState& state);
};

#endif

