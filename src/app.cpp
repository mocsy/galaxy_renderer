/*
 * app.cpp
 *
 *  Created on: 03.07.2015
 *      Author: scones
 */


#include "app.h"

#include <iostream>


extern app *pgalaxy_renderer;


app::app(std::uint64_t const number_of_stars)
  :
    m_number_of_stars(number_of_stars),
    m_glfw(),
    m_window(1980, 1080, "galaxy simulation by density wave", true),
    m_galaxy(
      13000.0,              // radius of the galaxy
      4000.0,               // radius of the core
      0.0005,               // angluar offset of the density wave per parsec of radius
      0.9,                  // excentricity at the edge of the core
      0.5,                  // excentricity at the edge of the disk
      0.5,
      200.0,                // orbital velocity at the edge of the core
      300.0,                // orbital velovity at the edge of the disk
      m_number_of_stars     // total number of stars
    ),
    m_va(),
    m_timer(),
    m_active(true)
{
}


app::~app() {
}


void app::init() {
  // init glfw
  m_glfw.init();
  glfwSetErrorCallback(&app::global_error_callback);

  // open window
  m_window.init();
  m_window.set_key_callback(&app::global_key_callback);
  m_window.make_current();

  // activate vertex_array
  m_va.init();

  // setup all the geometry
  m_galaxy.InitStars();
}


void app::run() {
  std::int64_t i = 0;
  m_timer.reset();
  do {
    glClearColor(0.5, 0.5, 0.5, 0.5);
    glClear(GL_COLOR_BUFFER_BIT);

    m_va.activate();

    m_galaxy.render();

    m_window.swap_buffers();
    glfwPollEvents();
    ++i;
  } while (!m_window.should_close() && m_active);

  std::cout << "frames rendered: " << i << std::endl;
}


void app::error_callback(int error, const char* description) {
  std::cerr << "GLFW error (" << error << "): " << description << std::endl;
}


void app::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
  switch (key) {
    case GLFW_KEY_ESCAPE:
      m_active = false;
      break;
  }
}


void app::global_error_callback(int error, const char* description) {
  pgalaxy_renderer->error_callback(error, description);
}


void app::global_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  pgalaxy_renderer->key_callback(window, key, scancode, action, mods);
}

