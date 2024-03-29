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

#include <GL/glew.h>
#include <iostream>
#include <algorithm>
#include <vector>

static GLuint texture_id;

static const char* c_vertex_script = R"(
  #version 330 core

  in vec2 vertexPosition;
  in vec2 textureCoordinateVert;

  out vec2 textureCoordinateFrag;

  void main() {
    textureCoordinateFrag = textureCoordinateVert;
    gl_Position = vec4(vertexPosition, 0.0, 1.0);
  }
)";

static const char* c_fragment_script = R"(
  #version 330 core

  uniform sampler2D screenState;
  in vec2 textureCoordinateFrag;

  out vec4 color;

  void main()
  {
    float color_value = texture(screenState, textureCoordinateFrag).r;

    color.r = color_value;
    color.g = color_value;
    color.b = color_value;
    color.a = 1.0;

    //if ((int(floor(textureCoordinateFrag.x + 0.5) + floor(textureCoordinateFrag.y + 0.5)) & 1) == 0)
    //  color = vec4(1.0, 1.0, 1.0, 1.0);
    //else
    //  color = vec4(0.0, 0.0, 0.0, 0.0);
  }
)";

static std::vector<float> quad_vertices {
  -1.0f, -1.0f,
  1.0f, -1.0f,
  1.0f, 1.0f,
  -1.0f, 1.0f,
};

static GLuint quad_vertices_id;

static std::vector<float> quad_vertex_textures{
  0.0f, 1.0f,
  1.0f, 1.0f,
  1.0f, 0.0f,
  0.0f, 0.0f,
};

static GLuint quad_vertex_textures_id;

static std::vector<int> quad_faces{
  0, 1, 2,
  0, 2, 3,
};

static GLuint quad_faces_id;

static void CheckGLError()
{
  GLenum error = GL_NO_ERROR;

  error = glGetError();

  if (GL_NO_ERROR != error)
  {
    std::cout << "OpenGL error: " << error << std::endl;
  }
}

GLuint CreateFragmentShader(int shader_type, const char* cscript)
{
  GLuint shaderUnitId = glCreateShader(shader_type);

  glShaderSource(shaderUnitId, 1, &cscript, NULL);
  glCompileShader(shaderUnitId);

  GLint result = GL_FALSE;
  int infoLogLength;

  glGetShaderiv(shaderUnitId, GL_COMPILE_STATUS, &result);
  glGetShaderiv(shaderUnitId, GL_INFO_LOG_LENGTH, &infoLogLength);

  std::cout << "Compiling shader... " << std::endl;

  if (infoLogLength > 0)
  {
    std::vector<char> vertexShaderErrorMessage(infoLogLength);
    glGetShaderInfoLog(shaderUnitId, infoLogLength, NULL, &vertexShaderErrorMessage[0]);

    std::cout << &vertexShaderErrorMessage[0] << std::endl;
  }

  CheckGLError();

  return shaderUnitId;
}

void CreateQuad(GLuint programID)
{
  // Process the vertices and pass them to OpenGL.

  glGenBuffers(1, &quad_vertices_id);
  glBindBuffer(GL_ARRAY_BUFFER, quad_vertices_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices[0]) * quad_vertices.size(), &quad_vertices[0], GL_STATIC_DRAW);

  const GLint quad_vertices_location = glGetAttribLocation(programID, "vertexPosition");
  glVertexAttribPointer(quad_vertices_location, 2, GL_FLOAT, GL_TRUE, 0, NULL);
  glEnableVertexAttribArray(quad_vertices_location);

  CheckGLError();

  // Process the texture coordinates and pass them to OpenGL.

  glGenBuffers(1, &quad_vertex_textures_id);
  glBindBuffer(GL_ARRAY_BUFFER, quad_vertex_textures_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertex_textures[0]) * quad_vertex_textures.size(), &quad_vertex_textures[0], GL_STATIC_DRAW);

  const GLint quad_vertex_textures_location = glGetAttribLocation(programID, "textureCoordinateVert");
  glVertexAttribPointer(quad_vertex_textures_location, 2, GL_FLOAT, GL_TRUE, 0, NULL);
  glEnableVertexAttribArray(quad_vertex_textures_location);

  CheckGLError();

  // Process the faces and pass them to OpenGL.

  glGenBuffers(1, &quad_faces_id);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad_faces_id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quad_faces[0]) * quad_faces.size(), &quad_faces[0], GL_STATIC_DRAW);

  CheckGLError();
}

// Adds the shader and makes it available to the renderer.
// @param shader The shader object.
GLuint CreateShaderProgram()
{
  GLuint programID = glCreateProgram();

  glAttachShader(programID, CreateFragmentShader(GL_VERTEX_SHADER, c_vertex_script));
  glAttachShader(programID, CreateFragmentShader(GL_FRAGMENT_SHADER, c_fragment_script));

  glLinkProgram(programID);

  GLint result = GL_FALSE;
  int infoLogLength;

  glGetProgramiv(programID, GL_LINK_STATUS, &result);
  glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);

  std::cout << "Linking shader... " << std::endl;

  if (infoLogLength > 0)
  {
    std::vector<char> programErrorMessage(infoLogLength);
    glGetProgramInfoLog(programID, infoLogLength, NULL, &programErrorMessage[0]);

    std::cout << &programErrorMessage[0] << std::endl;
  }

  CheckGLError();

  return programID;
}

void CreateSystemState(GLuint programID, std::array<uint8_t, Globals::NUM_PIXELS>& texture)
{
  glGenTextures(1, &texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, Globals::DISPLAY_COLUMNS, Globals::DISPLAY_ROWS, 0, GL_RED, GL_UNSIGNED_BYTE, texture.data());
  
  CheckGLError();

  GLint texture_location = glGetUniformLocation(programID, "screenState");

  CheckGLError();

  glUniform1i(texture_location, 0);
  
  CheckGLError();

  glActiveTexture(GL_TEXTURE0);

  CheckGLError();
}

Renderer::Renderer()
{
  GLenum err = glewInit();

  if (GLEW_OK != err)
  {
    std::cout << "Error loading GLEW: " << glewGetErrorString(err) << std::endl;
  }
  else
  {
    std::cout << "Using GLEW: " << glewGetString(GLEW_VERSION) << std::endl;
  }

  CheckGLError();

  int i = 0;
  std::for_each(texture.begin(), texture.end(), [&i](uint8_t &pixel)
  {
    pixel = (i % 2 == 0) ? 0xFF : 0;
    i++;
  });

  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glClearColor(0.0, 0.0, 0.0, 1.0);

  GLuint shader_id = CreateShaderProgram();

  glUseProgram(shader_id);

  CreateQuad(shader_id);
  CreateSystemState(shader_id, texture);
}

void Renderer::DrawScreen(const SystemState& state)
{
  bool changed = false;

  for (int x = 0; x < Globals::NUM_PIXELS; ++x)
  {
    uint8_t new_value = state.display[x] ? 0xFF : 0;

    if (texture[x] != new_value)
    {
      changed = true;
      texture[x] = new_value;
    }
  }

  if (changed)
  {
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, Globals::DISPLAY_COLUMNS, Globals::DISPLAY_ROWS, GL_RED, GL_UNSIGNED_BYTE, texture.data());

    CheckGLError();
  }

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glLoadIdentity();

  CheckGLError();

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad_faces_id);

  glDrawElements(GL_TRIANGLES, quad_faces.size(), GL_UNSIGNED_INT, (void*)(0));

  CheckGLError();
}
