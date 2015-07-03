/*
 * window.cpp
 *
 *  Created on: 16.08.2013
 *      Author: scn
 */


#include "core/window.h"


#include <stdexcept>
#include <iostream>


namespace core {

  void window::init() {
    auto previous_context = glfwGetCurrentContext();

    glfwWindowHint(GLFW_SAMPLES, m_anti_aliasing_level);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_open_gl_major_version);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_open_gl_minor_version);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_handle = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
    if (NULL == m_handle) {
      this->shutdown();
      throw std::runtime_error("window could not be initialised");
    }

    glfwMakeContextCurrent(m_handle);

    glewExperimental = GL_TRUE;
    auto glew_err = glewInit();
    if (glew_err != GLEW_OK) {
      this->shutdown();
      throw std::runtime_error("glew could not be initialised");
    }

    glfwMakeContextCurrent(previous_context);
  }


  void window::shutdown() {
    if (m_handle == glfwGetCurrentContext()) {
      glfwMakeContextCurrent(0);
    }
    glfwDestroyWindow(m_handle);
  }


  void window::make_current() {
    glfwMakeContextCurrent(m_handle);
  }


  bool window::should_close() {
    return glfwWindowShouldClose(m_handle);
  }


  void window::swap_buffers() {
    glfwSwapBuffers(m_handle);
  }

}

