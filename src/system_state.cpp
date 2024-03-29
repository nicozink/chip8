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
  address = 0;
  
  for (int i = 0; i < Globals::DISPLAY_ROWS; ++i)
  {
    for (int j = 0; j < Globals::DISPLAY_COLUMNS; ++j)
    {
      display[GetDisplayIndex(i, j)] = false;
    }
  }
  
  is_running = true;
  
  for (int i = 0; i < Globals::NUM_KEYS; ++i)
  {
    keyboard[i] = false;
  }

  std::for_each(memory.begin(), memory.end(), [](uint8_t &byte)
  {
    byte = 0;
  });
  
  program_counter = Globals::PROGRAM_OFFSET;
  
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

int SystemState::GetDisplayRow(int i)
{
  return i / Globals::DISPLAY_COLUMNS;
}

int SystemState::GetDisplayCol(int i)
{
  return i % Globals::DISPLAY_COLUMNS;
}

int SystemState::GetDisplayIndex(int r, int c)
{
  return r * Globals::DISPLAY_COLUMNS + c;
}
