/*
Copyright © 2012, Nico Zink
All rights reserved.
*/

#include "chip8_emulator.h" 

// Local Includes
#include "main.h"
#include "display.h"
#include "file_system.h"
#include "input.h"
#include "program_controller.h"
#include "system_state.h"

// Project Includes

// External Includes
#include <iostream>
#include <string>

// Runs the main program.
int run(std::string rom_location)
{
  SystemState state;
 
  FileSystem file_system;
  
  if (!file_system.LoadRom(state, rom_location))
  {
    std::cout << "Unable to load the ROM." << std::endl;
  }
  
  ProgramController controller;
  Display display;
  Input input;
  
  while (state.is_running)
  {
    input.Process(state);
    controller.Step(state);
    display.Refresh(state);
  }
  
  return 0;
}
