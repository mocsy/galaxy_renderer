/*
 * shader_program.cpp
 *
 *  Created on: 05.10.2013
 *      Author: scn
 */

#include "core/shader_program.h"
#include "core/shader.h"
#include "errors/shader_error.h"

#include <GL/glew.h>

#include <system_error>
#include <iostream>
#include <string.h>

namespace core {

  void shader_program::init() {
    m_handle = glCreateProgram();

    unsigned int shader_types[] = {
      GL_VERTEX_SHADER,
      GL_FRAGMENT_SHADER,
      GL_TESS_EVALUATION_SHADER,
      GL_TESS_CONTROL_SHADER,
      GL_GEOMETRY_SHADER,
      GL_COMPUTE_SHADER
    };

    unsigned int attached_shaders = 0;
    for (int i = 0; i < 6; ++i) {
      try {
        shader some_shader(m_name, shader_types[i]);
        some_shader.init();
        check_for_error(some_shader.get_result());
        glAttachShader(m_handle, some_shader.get_handle());
        ++attached_shaders;
      } catch (std::system_error const &e) {
        // ignore missing files
      } catch (std::runtime_error const &e) {
        // ignore empty files
      }
    }
    if (0 == attached_shaders)
      throw errors::shader_error("no shaders defined");

    glLinkProgram(m_handle);

    int result;
    glGetProgramiv(m_handle, GL_LINK_STATUS, &result);
    check_for_error(result);
  }


  void shader_program::shutdown() {
    glDeleteProgram(m_handle);
  }


  void shader_program::activate() {
    glUseProgram(m_handle);
  }


  int shader_program::get_uniform_location(std::string const& name) {
    return glGetUniformLocation(m_handle, name.c_str());
  }


  void shader_program::check_for_error(int result) {
    static const int buffer_size = 1024;

    int log_length = 0;
    glGetShaderiv(m_handle, GL_INFO_LOG_LENGTH, &log_length);

    if (log_length > 0) {
      log_length = std::min(log_length, buffer_size);
      char buffer[buffer_size];
      memset(buffer, 0, log_length);
      glGetShaderInfoLog(m_handle, log_length, 0, buffer);
      errors::shader_error compile_error(buffer);
      std::cerr << "shader buffer error length: " << log_length << "\nshader error: " << buffer << std::endl;
      throw compile_error;
    }
  }
}

