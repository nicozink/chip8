/*
Copyright © Nico Zink
All rights reserved.
*/

#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

// Local Includes

// Project Includes

// External Includes
#include <string>

// Required classes
class SystemState;

// A class which handles file input and output.
class FileSystem
{
  public:
  
    FileSystem();
    
    bool LoadRom(SystemState& system_state, std::string rom_location);
};

#endif

