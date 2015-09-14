/*
Copyright © Nico Zink
All rights reserved.
*/

#ifndef INPUT_H
#define INPUT_H

// Local Includes

// Project Includes

// External Includes

// Required classes
class SystemState;

// A class which handles the input for each frame.
class Input
{
  public:
  
    Input();
    
    void Process(SystemState& state);
};

#endif

