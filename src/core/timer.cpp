/*
 * timer.cpp
 *
 *  Created on: 11.01.2015
 *      Author: scn
 */


#include "core/timer.h"

#include <glfw/glfw3.h>

namespace core {

  void timer::init() {
    m_start_time = glfwGetTime();
  }


  void timer::shutdown() {
    m_start_time = 0.0;
  }


  double timer::elapsed_time() const {
    return glfwGetTime() - m_start_time;
  }
}

