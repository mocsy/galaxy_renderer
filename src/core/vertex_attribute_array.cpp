/*
 * vertex_attribute_array.cpp
 *
 *  Created on: 29.12.2014
 *      Author: scones
 */


#include "core/vertex_attribute_array.h"

#include <gl/glew.h>

namespace core {


  vertex_attribute_array::vertex_attribute_array(unsigned int layout_id) : m_id(layout_id) {
    glEnableVertexAttribArray(m_id);
  }


  vertex_attribute_array::~vertex_attribute_array() {
    glDisableVertexAttribArray(m_id);
  }

}

