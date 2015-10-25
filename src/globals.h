/*
Copyright © Nico Zink
All rights reserved.
*/

#ifndef GLOBALS_H
#define GLOBALS_H

// Local Includes

// Project Includes

// External Includes

// A class which represents the state of the system for the chip 8 virtual machine.
struct Globals
{
  public:
  
    static constexpr int DISPLAY_ROWS = 32;
    
    static constexpr int DISPLAY_COLUMNS = 64;
    
    static constexpr int FONT_OFFSET = 0;
    
    static constexpr int FONT_SIZE = 5;

    static constexpr int NUM_KEYS = 16;
    
    static constexpr int NUM_PIXELS = DISPLAY_ROWS * DISPLAY_COLUMNS;
    
    static constexpr int MEM_SIZE = 4095;
    
    static constexpr int PROGRAM_OFFSET = 0x200;
};

#endif

