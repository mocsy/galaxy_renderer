/*
 * glfw.cpp
 *
 *  Created on: 16.08.2013
 *      Author: scn
 */


#include "core/glfw.h"


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>


namespace core {

  void glfw::init() {
    glfwInit();
  }


  void glfw::shutdown() {
    glfwTerminate();
  }

}

