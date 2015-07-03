/*
 * star.cpp
 *
 *  Created on: 03.07.2015
 *      Author: scones
 */


#include "star.h"


star::star()
  :
    m_theta(0.0),
    m_velTheta(0.0),
    m_angle(0.0),
    m_a(0.0),
    m_b(0.0),
    m_temp(0.0),
    m_mag(0.0),
    m_center(core::t_vec2d()),
    m_vel(core::t_vec2d()),
    m_pos(core::t_vec2d())
{
}


star::star(
  double const& theta,
  double const& vel_theta,
  double const& angle,
  double const& minor_half_axis,
  double const& major_half_axis,
  double const& temperature,
  core::t_vec2d const& center,
  double const brightness
) :
  m_theta(theta),
  m_velTheta(vel_theta),
  m_angle(angle),
  m_a(minor_half_axis),
  m_b(major_half_axis),
  m_temp(temperature),
  m_mag(brightness),
  m_center(center),
  m_vel(core::t_vec2d()),
  m_pos(core::t_vec2d())
{
}


core::t_vec2d const& star::CalcXY() {
  double beta = -m_angle,
         alpha = glm::radians(m_theta);

  // temporaries to save cpu time
  double cos_alpha = cos(alpha),
         sin_alpha = sin(alpha),
         cos_beta = cos(beta),
         sin_beta = sin(beta);

  m_pos = m_center + core::t_vec2d((m_a * cos_alpha * cos_beta - m_b * sin_alpha * sin_beta), (m_a * cos_alpha * sin_beta + m_b * sin_alpha * cos_beta));
  return m_pos;
}


star& star::operator=(star& rhs) {
  this->m_theta    = rhs.m_theta;
  this->m_velTheta = rhs.m_velTheta;
  this->m_angle    = rhs.m_angle;
  this->m_a        = rhs.m_a;
  this->m_b        = rhs.m_b;
  this->m_temp     = rhs.m_temp;
  this->m_mag      = rhs.m_mag;
  this->m_center   = rhs.m_center;
  this->m_vel      = rhs.m_vel;
  this->m_pos      = rhs.m_pos;

  return *this;
}


star& star::operator=(star&& rhs) {
  this->m_theta    = rhs.m_theta;
  this->m_velTheta = rhs.m_velTheta;
  this->m_angle    = rhs.m_angle;
  this->m_a        = rhs.m_a;
  this->m_b        = rhs.m_b;
  this->m_temp     = rhs.m_temp;
  this->m_mag      = rhs.m_mag;
  this->m_center   = rhs.m_center;
  this->m_vel      = rhs.m_vel;
  this->m_pos      = rhs.m_pos;

  return *this;
}

