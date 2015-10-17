/*
Copyright © Nico Zink
All rights reserved.
*/

#include "timers.h" 

// Local Includes
#include "system.h"
#include "system_state.h"

// Project Includes

// External Includes

Timers::Timers()
{
  
}

void Timers::Count(SystemState& state)
{
  if (state.delay_timer > 0)
  {
    --state.delay_timer;
  }
}
