/*
Copyright © Nico Zink
All rights reserved.
*/

#include "renderer.h" 

// Local Includes
#include "system_state.h"

// Project Includes

// External Includes
#include <GL/gl.h>
#include <iostream>

Renderer::Renderer()
{
  
}

void Renderer::DrawScreen(const SystemState& state)
{
  for (int x = 0; x < Globals::NUM_PIXELS; ++x)
  {
    if (state.display[x])
    {
      const int row = x / Globals::DISPLAY_COLUMNS;
      const int column = x % Globals::DISPLAY_ROWS;
      
      DrawQuad(row, column, row + 1, column + 1);
    }
  }
}

void Renderer::CheckGLError()
{
  GLenum error = GL_NO_ERROR;
  
  error = glGetError();

  if (GL_NO_ERROR != error)
  {
    std::cout << "OpenGL error: " << error << std::endl;
  }
}

void Renderer::DrawQuad(float x1, float y1, float x2, float y2)
{
  glColor3f(0.0, 0.0, 0.0);
  
  glBegin(GL_QUADS);
  
  glVertex3d(x1, y1, 0.0);
  glVertex3d(x1, y2, 0.0);
  glVertex3d(x2, y2, 0.0);
  glVertex3d(x2, y1, 0.0);
  
  glEnd();

  CheckGLError();
}
