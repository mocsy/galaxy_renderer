/*
 * star_particles.h
 *
 *  Created on: 06.07.2015
 *      Author: scones
 */

#ifndef INCLUDE_STAR_PARTICLES_H_
#define INCLUDE_STAR_PARTICLES_H_


#include "core/vertex_array.h"
#include "core/vertex_buffer.h"
#include "core/texture.h"
#include "core/shader_program.h"
#include "core/timer.h"
#include <cinttypes>


class star_particles {

  public:


  struct star {
    float a;
    float b;
    float theta;
    float angle;
    float theta_velocity;
    float temperature;
    float brightness;
  };


  star_particles(std::vector<star_particles::star> const& stars);
  ~star_particles() = default;

  void render();

  protected:


  core::vertex_array m_vertex_array;
  core::shader_program m_shader_program;
  core::vertex_buffer m_stars_buffer;    // stars objects, read with strides
  core::vertex_buffer m_star_attributes_buffer;
  core::texture m_sprite;
  int m_texture_uniform_location;
  std::uint64_t m_number_of_stars;
  core::timer m_timer;
};


#endif /* INCLUDE_STAR_PARTICLES_H_ */

