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
#include "Galaxy.h"


class app {

  public:


  app(std::uint64_t const number_of_stars);

  void init();
  void run();


  protected:


  std::uint64_t m_number_of_stars;
  core::glfw m_glfw;
  core::window m_window;
  Galaxy m_galaxy;
};


#endif /* INCLUDE_APP_H_ */

