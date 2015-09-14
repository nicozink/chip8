/*
Copyright © Nico Zink
All rights reserved.
*/

#include "input.h" 

// Local Includes
#include "system_state.h"

// Project Includes

// External Includes
#include <SDL/SDL.h>

Input::Input()
{
  
}

void Input::Process(SystemState& state)
{
  SDL_Event event;

  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
      case SDL_QUIT:
      {
        state.is_running = false;

        break;
      }
      case SDL_KEYDOWN:
      case SDL_KEYUP:
      {
        break;
      }
      default:
        break;
    }
  }
}
