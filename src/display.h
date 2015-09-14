/*
Copyright © Nico Zink
All rights reserved.
*/

#ifndef DISPLAY_H
#define DISPLAY_H

// Local Includes
#include <renderer.h>

// Project Includes

// External Includes

// Required classes
class SystemState;

// A class which displays the screen for each frame.
class Display
{
  public:
  
    Display();
    
    void Refresh(const SystemState& state);
    
  private:
  
    Renderer renderer;
};

#endif

