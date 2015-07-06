/*
 * star_particles.cpp
 *
 *  Created on: 06.07.2015
 *      Author: scones
 */


#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include "star_particles.h"
#include "core/vertex_attribute_array.h"
#include "core/types.h"


star_particles::star_particles(std::vector<star_particles::star> const& stars)
  :
    m_vertex_array(),
    m_shader_program("stars"),
    m_stars_buffer(),
    m_star_attributes_buffer(),
    m_sprite(0),
    m_texture_uniform_location(GL_FALSE),
    m_number_of_stars(stars.size()),
    m_timer()
{
  m_vertex_array.init();
  m_vertex_array.activate();
  m_shader_program.init();
  m_texture_uniform_location = m_shader_program.get_uniform_location("sprite");

  m_stars_buffer.init();
  m_stars_buffer.activate();
  std::vector<core::t_vec4f> polar_coordinates;
  std::vector<core::t_vec3f> attributes;
  for (auto const& star : stars) {
    polar_coordinates.push_back(core::t_vec4f(star.a, star.b, star.theta, star.angle));
    attributes.push_back(core::t_vec3f(star.theta_velocity, star.temperature, star.brightness));
  }
  glBufferData(GL_ARRAY_BUFFER, sizeof(core::t_vec4f) * polar_coordinates.size(), polar_coordinates.data(), GL_STATIC_DRAW);

  m_star_attributes_buffer.init();
  m_star_attributes_buffer.activate();
  glBufferData(GL_ARRAY_BUFFER, sizeof(core::t_vec3f) * attributes.size(), attributes.data(), GL_STATIC_DRAW);

  m_timer.init();
}


void star_particles::render() {
  static const int position_layout_id = 1;
  static const int attributes_layout_id = 2;

  static float rotation = 0.0;
  rotation += 0.0001;

  glm::mat4 view(glm::lookAt<float, glm::highp>(
    core::t_vec3f(0.0f, 0.0f, 30000.0f),
    core::t_vec3f(0.0f, 0.0f, 0.0f),
    core::t_vec3f(0.0f, 1.0f, 0.0f)
  ));
  glm::mat4 projection(glm::perspective<float>(45.0f, 16.0f/9.0f, 0.01, 100000000000.0f));
  glm::mat4 model(1.0f);
  glm::mat4 world = projection * view * model;

  m_vertex_array.activate();

  glEnable(GL_POINT_SPRITE);
  glEnable(GL_PROGRAM_POINT_SIZE);
  glDepthRange(0.01, 1000000.0);

  m_shader_program.activate();

  auto rotation_id = m_shader_program.get_uniform_location("world_matrix");
  glUniformMatrix4fv(rotation_id, 1, GL_FALSE, &world[0][0]);

  auto timer_id = m_shader_program.get_uniform_location("time");
  glUniform1f(timer_id, (float)m_timer.elapsed_time());

  auto pi_id = m_shader_program.get_uniform_location("pi");
  glUniform1f(pi_id, glm::pi<float>());

  m_stars_buffer.activate();

  // use a, b, theta and angle
  glVertexAttribPointer(position_layout_id,   4, GL_FLOAT, GL_FALSE, 3 * sizeof(double), nullptr);
  core::vertex_attribute_array position(position_layout_id);

  // use theta velocity, temperature and brightness
  glVertexAttribPointer(attributes_layout_id, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(double), (void*)(4 * sizeof(double)));
  core::vertex_attribute_array attributes(attributes_layout_id);

  glDrawArrays(GL_POINTS, 0, m_number_of_stars);
}

