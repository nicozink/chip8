/*
Copyright © Nico Zink
All rights reserved.
*/

#ifndef PROGRAM_CONTROLLER_H
#define PROGRAM_CONTROLLER_H

// Local Includes

// Project Includes

// External Includes

// Required classes
class SystemState;

// A class which handles execution of the game.
class ProgramController
{
  public:
  
    ProgramController();
    
    void Step(SystemState& system_state);
};

#endif

