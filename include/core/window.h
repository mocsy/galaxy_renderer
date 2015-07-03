/*
 * window.h
 *
 *  Created on: 16.08.2013
 *      Author: scn
 */

#ifndef WINDOW_H_
#define WINDOW_H_


#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace core {

  class window {
    public:


    window(int width, int height, std::string const & title, int anti_aliasing_level = 0, int open_gl_major = 4, int open_gl_minor = 2, GLFWwindow* parent = nullptr, GLFWmonitor* monitor = nullptr)
      :
        m_handle(nullptr),
        m_parent(parent),
        m_monitor(monitor),
        m_title(title),
        m_width(width),
        m_height(height),
        m_anti_aliasing_level(anti_aliasing_level),
        m_open_gl_major_version(open_gl_major),
        m_open_gl_minor_version(open_gl_minor)
    {

    }

    ~window() {
      shutdown();
    }
    window(window&)  = delete;
    window(window&& right) {
      this->m_handle = right.m_handle;
      this->m_parent = right.m_parent;
      this->m_monitor = right.m_monitor;
      this->m_title = right.m_title;
      this->m_width = right.m_width;
      this->m_height = right.m_height;
      this->m_anti_aliasing_level = right.m_anti_aliasing_level;
      this->m_open_gl_major_version = right.m_open_gl_major_version;
      this->m_open_gl_minor_version = right.m_open_gl_minor_version;

      right.m_handle = nullptr;
      right.m_parent = nullptr;
      right.m_monitor = nullptr;
    }


    void init();
    void shutdown();

    GLFWwindow * const get_handle() const { return m_handle; }
    void make_current();
    bool should_close();
    void swap_buffers();

    float get_inverse_width() const { return 1.0f/static_cast<float>(m_width); }
    float get_inverse_height() const { return 1.0f/static_cast<float>(m_height); }


    protected:


    GLFWwindow*  m_handle;

    GLFWwindow*  m_parent;
    GLFWmonitor* m_monitor;
    std::string  m_title;

    int m_width;
    int m_height;
    int m_anti_aliasing_level;
    int m_open_gl_major_version;
    int m_open_gl_minor_version;
  };

}

#endif /* WINDOW_H_ */

