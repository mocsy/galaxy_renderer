/*
 * star.cpp
 *
 *  Created on: 03.07.2015
 *      Author: scones
 */


#include "star.h"


star::star()
    : m_theta(0), m_a(0), m_b(0), m_center(0, 0) {
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

