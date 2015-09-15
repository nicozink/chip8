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
    
    double GetScreenX(int c);
    
    double GetScreenY(int r);
    
    void DrawQuad(int r, int c);
};

#endif

