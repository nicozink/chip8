/*
Copyright © Nico Zink
All rights reserved.
*/

#ifndef FONT_H
#define FONT_H

// Local Includes
#include <stdint.h>

// Project Includes

// External Includes

// Required classes
class SystemState;

// A class which handles loading the font into memory.
class Font
{
  public:
  
    Font();
    
    void Load(SystemState& system_state);
};

#endif

