/*
 * app.h
 *
 *  Created on: 03.07.2015
 *      Author: scones
 */

#ifndef INCLUDE_APP_H_
#define INCLUDE_APP_H_


#include <cinttypes>


#include "core/window.h"
#include "core/glfw.h"
#include "core/vertex_array.h"
#include "core/timer.h"
#include "Galaxy.h"


class app {

  public:


  app(std::uint64_t const number_of_stars);
  ~app();

  void init();
  void run();


  protected:


  void error_callback(int error, const char* description);
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

  static void global_error_callback(int error, const char* description);
  static void global_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);


  std::uint64_t m_number_of_stars;
  core::glfw m_glfw;
  core::window m_window;
  Galaxy m_galaxy;
  core::vertex_array m_va;
  core::timer m_timer;
  bool m_active;

  void initialize_galaxy_objects();
};


#endif /* INCLUDE_APP_H_ */

