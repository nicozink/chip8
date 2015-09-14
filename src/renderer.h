/*
Copyright © Nico Zink
All rights reserved.
*/

#ifndef RENDERER_H
#define RENDERER_H

// Local Includes

// Project Includes

// External Includes

// Required classes
class SystemState;

// A class which displays the screen for each frame.
class Renderer
{
  public:
  
    Renderer();
    
    void DrawScreen(const SystemState& state);
    
  private:
  
    void CheckGLError();
    
    void DrawQuad(float x1, float y1, float x2, float y2);
};

#endif

