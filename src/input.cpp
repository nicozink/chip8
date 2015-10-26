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
        int keyPressed = -1;

        SDLKey sdlKeyPressed = event.key.keysym.sym;

        switch (sdlKeyPressed)
        {
          case SDLK_x:
            keyPressed = 0;
            break;

          case SDLK_1:
            keyPressed = 1;
            break;

          case SDLK_2:
            keyPressed = 2;
            break;

          case SDLK_3:
            keyPressed = 3;
            break;

          case SDLK_q:
            keyPressed = 4;
            break;

          case SDLK_w:
            keyPressed = 5;
            break;

          case SDLK_e:
            keyPressed = 6;
            break;

          case SDLK_a:
            keyPressed = 7;
            break;

          case SDLK_s:
            keyPressed = 8;
            break;

          case SDLK_d:
            keyPressed = 9;
            break;

          case SDLK_z:
            keyPressed = 10;
            break;

          case SDLK_c:
            keyPressed = 11;
            break;

          case SDLK_4:
            keyPressed = 12;
            break;

          case SDLK_r:
            keyPressed = 13;
            break;

          case SDLK_f:
            keyPressed = 14;
            break;

          case SDLK_v:
            keyPressed = 15;
            break;
        }

        if (keyPressed != -1)
        {
          state.keyboard[keyPressed] = event.type == SDL_KEYDOWN;
        }

        break;
      }
      default:
        break;
    }
  }
}
