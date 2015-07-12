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

  window::window(int width, int height, std::string const & title, bool fullscreen, int anti_aliasing_level, int open_gl_major, int open_gl_minor, GLFWwindow* parent, GLFWmonitor* monitor)
    :
      m_handle(nullptr),
      m_parent(parent),
      m_monitor(monitor),
      m_title(title),
      m_width(width),
      m_height(height),
      m_anti_aliasing_level(anti_aliasing_level),
      m_open_gl_major_version(open_gl_major),
      m_open_gl_minor_version(open_gl_minor),
      m_fullscreen(fullscreen)
  {

  }

  void window::init() {

    auto previous_context = glfwGetCurrentContext();

    glfwWindowHint(GLFW_SAMPLES, m_anti_aliasing_level);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_open_gl_major_version);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_open_gl_minor_version);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (m_fullscreen) {
      if (!m_monitor) {
        m_monitor = glfwGetPrimaryMonitor();
      }
      const GLFWvidmode* mode = glfwGetVideoMode(m_monitor);

      m_width = mode->width;
      m_height = mode->height;

      glfwWindowHint(GLFW_RED_BITS, mode->redBits);
      glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
      glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
      glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
      glfwWindowHint(GLFW_AUTO_ICONIFY, GL_FALSE);
    }

    m_handle = glfwCreateWindow(m_width, m_height, m_title.c_str(), m_monitor, NULL);
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


  void window::set_key_callback(GLFWkeyfun key_callback_function) {
    glfwSetKeyCallback(m_handle, key_callback_function);
  }
}

