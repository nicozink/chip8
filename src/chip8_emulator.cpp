/*
Copyright © 2012, Nico Zink
All rights reserved.
*/

#include "chip8_emulator.h" 

// Local Includes
#include "main.h"
#include "display.h"
#include "input.h"
#include "system_state.h"

// Project Includes

// External Includes
#include <iostream>

// Runs the main program.
int run()
{
  SystemState state;
  
  Display display;
  Input input;
  
  while (state.is_running)
  {
    input.Process(state);
    display.Refresh(state);
  }
  
  return 0;
}
