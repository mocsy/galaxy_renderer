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


  std::uint64_t m_number_of_stars;
  core::glfw m_glfw;
  core::window m_window;
  Galaxy m_galaxy;
  core::vertex_array m_va;
  core::timer m_timer;

  void initialize_galaxy_objects();
};


#endif /* INCLUDE_APP_H_ */

