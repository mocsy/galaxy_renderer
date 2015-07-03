/*
 * app.h
 *
 *  Created on: 03.07.2015
 *      Author: scones
 */

#ifndef INCLUDE_APP_H_
#define INCLUDE_APP_H_


#include "core/window.h"
#include "core/glfw.h"
#include <cinttypes>


class app {

  public:


  app(std::uint64_t const number_of_stars);

  void init();
  void run();


  protected:


  std::uint64_t m_number_of_stars;
  core::glfw m_glfw;
  core::window m_window;
};


#endif /* INCLUDE_APP_H_ */

