/*
 * texture.cpp
 *
 *  Created on: 21.09.2014
 *      Author: scn
 */

#include "core/texture.h"


#include <gl/glew.h>


namespace core {

  void texture::activate() {
    glActiveTexture(GL_TEXTURE0 + m_id);
    glBindTexture(GL_TEXTURE_2D, m_handle);
  }


  void texture::init() {
    glActiveTexture(GL_TEXTURE0 + m_id);

    glGenTextures(1, &m_handle);

    glBindTexture(GL_TEXTURE_2D, m_handle);
  }


  void texture::shutdown() {
    glDeleteTextures(1, &m_handle);
  }
}

