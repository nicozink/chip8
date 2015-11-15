/*
Copyright © Nico Zink
All rights reserved.
*/

#ifndef MEMORY_H
#define MEMORY_H

// Local Includes
#include "globals.h"
#include "timer.h"

// Project Includes

// External Includes
#include <array>
#include <bitset>
#include <stdint.h>

// A class which represents the state of the system for the chip 8 virtual machine.
struct SystemState
{
  public:
  
    SystemState();
    
    static int GetDisplayRow(int i);
    static int GetDisplayCol(int i);
    static int GetDisplayIndex(int r, int c);
    
    uint16_t address;
    
    Timer<Globals::TIMER_FREQUENCY> delay_timer;
    
    std::bitset<Globals::NUM_PIXELS> display;
    
    bool is_running;
    
    std::bitset<Globals::NUM_KEYS> keyboard;

    std::array<uint8_t, Globals::MEM_SIZE> memory;
    
    uint16_t program_counter;
    
    std::array<uint8_t, 16> registers;
    
    uint8_t sound_timer;
    
    std::array<uint16_t, 16> stack;
    
    uint8_t stack_pointer;
};

#endif

