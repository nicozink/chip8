/*
Copyright © Nico Zink
All rights reserved.
*/

#include "system_state.h" 

// Local Includes

// Project Includes

// External Includes
#include <algorithm>

SystemState::SystemState()
{
  delay_timer = 0;
  
  for (int i = 0; i < Globals::NUM_PIXELS; ++i)
  {
    display[i] = 0;
  }
  
  is_running = true;
  
  std::for_each(memory.begin(), memory.end(), [](uint8_t &byte)
  {
    byte = 0;
  });
  
  program_counter = 0;
  
  std::for_each(registers.begin(), registers.end(), [](uint8_t &byte)
  {
    byte = 0;
  });
  
  sound_timer = 0;
  
  std::for_each(stack.begin(), stack.end(), [](uint16_t &byte)
  {
    byte = 0;
  });
  
  stack_pointer = 0;
}
