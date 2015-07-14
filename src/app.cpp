/*
 * app.cpp
 *
 *  Created on: 03.07.2015
 *      Author: scones
 */


#include "app.h"

#include <iostream>
#include <algorithm>

extern app *pgalaxy_renderer;


app::app(std::uint64_t const number_of_stars)
  :
    m_number_of_stars(number_of_stars),
    m_glfw(),
    m_window(1980, 1080, "galaxy simulation by density wave", false),
    m_va(),
    m_timer(),
    m_active(true),
    m_inner_excentricity(0.9),
    m_outer_excentricity(0.5),
    m_angular_offset(0.0005),
    m_core_radius(4000.0),
    m_galaxy_radius(13000.0),
    m_sigma(0.5),
    m_pgalaxy(nullptr)
{
  m_pgalaxy = new Galaxy(
    m_galaxy_radius,       // radius of the galaxy
    m_core_radius,         // radius of the core
    m_angular_offset,      // angluar offset of the density wave per parsec of radius
    m_inner_excentricity,  // excentricity at the edge of the core
    m_outer_excentricity,  // excentricity at the edge of the disk
    m_sigma,
    CORE_ORBIT_VELOCITY,   // orbital velocity at the edge of the core
    DISC_ORBIT_VELOCITY,   // orbital velovity at the edge of the disk
    m_number_of_stars      // total number of stars
  );
}


app::~app() {
  delete m_pgalaxy;
  m_pgalaxy = nullptr;
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
  m_pgalaxy->InitStars();
}


void app::run() {
  std::int64_t i = 0;
  m_timer.reset();
  do {
    glClearColor(0.5, 0.5, 0.5, 0.5);
    glClear(GL_COLOR_BUFFER_BIT);

    m_va.activate();

    if (m_pgalaxy)
      m_pgalaxy->render();

    m_window.swap_buffers();
    glfwPollEvents();
    ++i;
  } while (!m_window.should_close() && m_active);

  std::cout << "frames rendered: " << i << std::endl;
  std::cout << "fps: " << (double)i / m_timer.elapsed_time() << std::endl;
}


void app::error_callback(int error, const char* description) {
  std::cerr << "GLFW error (" << error << "): " << description << std::endl;
}


void app::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
  bool rebuild_galaxy = false;
  switch (key) {
    if (GLFW_RELEASE == action) {
      case GLFW_KEY_ESCAPE:
        m_active = false;
        break;

      // inner excentricity
      case GLFW_KEY_Q:
        m_inner_excentricity = std::min(0.95, m_inner_excentricity + 0.01);
        rebuild_galaxy = true;
        break;
      case GLFW_KEY_A:
        m_inner_excentricity = std::max(0.05, m_inner_excentricity - 0.01);
        rebuild_galaxy = true;
        break;

      // outer excentricity
      case GLFW_KEY_W:
        m_outer_excentricity = std::min(0.95, m_outer_excentricity + 0.01);
        rebuild_galaxy = true;
        break;
      case GLFW_KEY_S:
        m_outer_excentricity = std::max(0.05, m_outer_excentricity - 0.01);
        rebuild_galaxy = true;
        break;

      // angular offset
      case GLFW_KEY_E:
        m_angular_offset += 0.00005;
        rebuild_galaxy = true;
        break;
      case GLFW_KEY_D:
        m_angular_offset -= 0.00005;
        rebuild_galaxy = true;
        break;

      // core radius
      case GLFW_KEY_R:
        std::min(m_galaxy_radius, m_core_radius + 500.0);
        rebuild_galaxy = true;
        break;
      case GLFW_KEY_F:
        m_core_radius = std::max(0.0, m_core_radius - 500.0);
        rebuild_galaxy = true;
        break;

      // galaxy radius
      case GLFW_KEY_T:
        m_galaxy_radius += 1000.0;
        rebuild_galaxy = true;
        break;
      case GLFW_KEY_G:
        if (m_galaxy_radius - 1000.0 > m_core_radius)
          m_galaxy_radius -= 1000.0;
        rebuild_galaxy = true;
        break;

      // sigma
      case GLFW_KEY_Z:
      case GLFW_KEY_Y:
        m_sigma += 0.05;
        rebuild_galaxy = true;
        break;
      case GLFW_KEY_H:
        m_sigma = std::max(0.05, m_sigma - 0.05);
        rebuild_galaxy = true;
        break;
    }
  }

  if (rebuild_galaxy) {

    Galaxy *new_galaxy = new Galaxy(
      m_galaxy_radius,       // radius of the galaxy
      m_core_radius,         // radius of the core
      m_angular_offset,      // angluar offset of the density wave per parsec of radius
      m_inner_excentricity,  // excentricity at the edge of the core
      m_outer_excentricity,  // excentricity at the edge of the disk
      m_sigma,
      CORE_ORBIT_VELOCITY,   // orbital velocity at the edge of the core
      DISC_ORBIT_VELOCITY,   // orbital velovity at the edge of the disk
      m_number_of_stars      // total number of stars
    );
    auto tmp_galaxy = m_pgalaxy;
    m_pgalaxy = new_galaxy;
    delete tmp_galaxy;
    std::cerr << "1";
    m_pgalaxy->InitStars();
    rebuild_galaxy = false;
  }
}


void app::global_error_callback(int error, const char* description) {
  pgalaxy_renderer->error_callback(error, description);
}


void app::global_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  pgalaxy_renderer->key_callback(window, key, scancode, action, mods);
}

