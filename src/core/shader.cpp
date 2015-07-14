/*
 * shader.cpp
 *
 *  Created on: 03.10.2013
 *      Author: scn
 */

#include "core/shader.h"
#include "errors/shader_error.h"
#include "core/file.h"

#ifdef DEBUG
#include "debug/logger.h"
#endif

#include <GL/glew.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdexcept>
#include <cstdio>


namespace core {


  void shader::init() {
    std::string shader_content = file::content(file_path_name());
    if (0 == shader_content.size()) {
      char buffer[1024];
      std::vsnprintf(buffer, 1024, "file is empty '%s'", const_cast<char*>(file_path_name().c_str()));
      throw std::runtime_error((char*)buffer);
    }
    GLchar const* const c_shader_content = shader_content.c_str();
std::cout << "shader_content:\n'" << shader_content << "'" << std::endl;
    // initialize
    m_handle = glCreateShader(m_type);

    if (!m_handle)
      throw std::runtime_error("glCreateShader failed");

    glShaderSource(m_handle, 1, &c_shader_content, nullptr);
    glCompileShader(m_handle);
    check_for_error(m_result);
  }


  void shader::shutdown() {
    glDeleteShader(m_handle);
    m_handle = 0;
  }


  std::string shader::file_path_name() {
    std::string path_name("data/shaders/" + m_name);
    switch (m_type) {
      case GL_VERTEX_SHADER:
	path_name += ".v";
	break;
      case GL_FRAGMENT_SHADER:
	path_name += ".f";
	break;
      case GL_TESS_EVALUATION_SHADER:
	path_name += ".te";
	break;
      case GL_TESS_CONTROL_SHADER:
	path_name += ".tc";
	break;
      case GL_GEOMETRY_SHADER:
	path_name += ".g";
	break;
      case GL_COMPUTE_SHADER:
	path_name += ".cs";
	break;
      default:
	throw errors::shader_error(std::string("no such shader type:") + std::to_string(m_type));
    }

    return path_name;
  }


  void shader::check_for_error(int result) {
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

