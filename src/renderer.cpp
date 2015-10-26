/*
Copyright © Nico Zink
All rights reserved.
*/

#include "renderer.h" 

// Local Includes
#include "system.h"
#include "system_state.h"

// Project Includes

// External Includes
#if OPERATING_SYSTEM == WINDOWS
#include <windows.h>
#endif

#include <GL/gl.h>
#include <iostream>

Renderer::Renderer()
{
  
}

void Renderer::DrawScreen(const SystemState& state)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(0, 0, 0, 1.0);
  glLoadIdentity();
  glScalef(1.0, -1.0, 1.0);

  CheckGLError();
  
  for (int x = 0; x < Globals::NUM_PIXELS; ++x)
  {
    if (state.display[x])
    {
      const int row = SystemState::GetDisplayRow(x);
      const int column = SystemState::GetDisplayCol(x);
      
      DrawQuad(row, column);
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

void Renderer::DrawQuad(int r, int c)
{
  double x1 = GetScreenX(c);
  double y1 = GetScreenY(r);
  double x2 = GetScreenX(c + 1);
  double y2 = GetScreenY(r + 1);
  
  glColor3f(1.0, 1.0, 1.0);
  
  glBegin(GL_QUADS);
  
  glVertex3d(x1, y1, 0.0);
  glVertex3d(x1, y2, 0.0);
  glVertex3d(x2, y2, 0.0);
  glVertex3d(x2, y1, 0.0);
  
  glEnd();

  CheckGLError();
}

double Renderer::GetScreenX(int c)
{
  return (double)c / (double)(Globals::DISPLAY_COLUMNS) * 2.0 - 1.0;
}

double Renderer::GetScreenY(int r)
{
  return (double)r / (double)(Globals::DISPLAY_ROWS) * 2.0 - 1.0;
}
