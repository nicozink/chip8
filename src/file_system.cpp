/*
Copyright © Nico Zink
All rights reserved.
*/

#include "file_system.h" 

// Local Includes
#include "globals.h"
#include "system_state.h"

// Project Includes

// External Includes
#include <fstream>
#include <iostream>

FileSystem::FileSystem()
{
  
}

bool FileSystem::LoadRom(SystemState& state, std::string rom_location)
{
	FILE *file = fopen(rom_location.c_str(), "rb");
	if (!file)
	{
    std::cout << "Could not open the file." << std::endl;
    
		return false;
	}
	
  // The program starts after an initial section of system memory.
  uint8_t* program_memory = (&state.memory.data()[Globals::PROGRAM_OFFSET]);
  
	//Read file contents into buffer
	int read = fread(program_memory, sizeof(uint8_t), Globals::MEM_SIZE - Globals::PROGRAM_OFFSET, file);
	
  fclose(file);

  if (read)
  {
    std::cout << "Read " << read << " bytes from the file." << std::endl;
    
    return true;
  }
  else
  {
    std::cout << "No data was read from the file." << std::endl;
    
    return false;
  }
}
