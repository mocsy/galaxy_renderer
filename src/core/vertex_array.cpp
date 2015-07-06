/*
 * vertex_array.cpp
 *
 *  Created on: 29.12.2014
 *      Author: scones
 */



#include "core/vertex_array.h"
#include <GL/glew.h>


namespace core {
  void vertex_array::init() {
    glGenVertexArrays(m_count, &m_handle);
  }


  void vertex_array::shutdown() {
    glDeleteVertexArrays(m_count, &m_handle);
  }


  void vertex_array::activate() {
    glBindVertexArray(m_handle);
  }


  void vertex_array::deactivate() {
    glBindVertexArray(0);
  }
}

