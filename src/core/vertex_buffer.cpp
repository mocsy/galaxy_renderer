/*
 * vertex_buffer.cpp
 *
 *  Created on: 20.10.2013
 *      Author: scn
 */

#include "core/vertex_buffer.h"
#include "core/types.h"

#include <iostream>

namespace core {

  template <>
  void vertex_buffer::set_data(std::vector<t_vec2f> const& data) {
    activate();
    glBufferData(GL_ARRAY_BUFFER, sizeof(t_vec2f) * data.size(), data.data(), GL_STATIC_DRAW);
  }


  template <>
  void vertex_buffer::set_data(std::vector<t_vec2d> const& data) {
    activate();
    glBufferData(GL_ARRAY_BUFFER, sizeof(t_vec2d) * data.size(), &data[0], GL_STATIC_DRAW);
  }


  template <>
  void vertex_buffer::set_data(std::vector<t_vec3f> const& data) {
    activate();
    glBufferData(GL_ARRAY_BUFFER, sizeof(t_vec3f) * data.size(), data.data(), GL_STATIC_DRAW);
  }


  template <>
  void vertex_buffer::set_data(std::vector<t_vec3d> const& data) {
    activate();
    glBufferData(GL_ARRAY_BUFFER, sizeof(t_vec3d) * data.size(), &data[0], GL_STATIC_DRAW);
  }


  template <>
  void vertex_buffer::set_data(std::vector<t_vec4f> const& data) {
    activate();
    glBufferData(GL_ARRAY_BUFFER, sizeof(t_vec4f) * data.size(), data.data(), GL_STATIC_DRAW);
  }


  template <>
  void vertex_buffer::set_data(std::vector<t_vec4d> const& data) {
    activate();
    glBufferData(GL_ARRAY_BUFFER, sizeof(t_vec4d) * data.size(), data.data(), GL_STATIC_DRAW);
  }

  template <>
  void vertex_buffer::set_data(std::vector<float> const& data, unsigned int vector_size, unsigned int vertex_size) {
    activate();
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), data.data(), GL_STATIC_DRAW);
  }

  template <>
  void vertex_buffer::set_data(std::vector<double> const& data, unsigned int vector_size, unsigned int vertex_size) {
    activate();
    glBufferData(GL_ARRAY_BUFFER, sizeof(double) * data.size(), (double*)&data[0], GL_STATIC_DRAW);
  }
}

