/*
 * star.h
 *
 *  Created on: 03.07.2015
 *      Author: scones
 */

#ifndef INCLUDE_STAR_H_
#define INCLUDE_STAR_H_


#include <core/vectors.h>


struct star {
  public:

  star();
  star(
    double const& theta,
    double const& vel_theta,
    double const& angle,
    double const& minor_half_axis,
    double const& major_half_axis,
    double const& temperature,
    core::t_vec2d const& center,
    double const brightness = double()
  );

  star(star&)  = default;
  star(star&&) = default;
  ~star()      = default;

  star& operator=(star&);
  star& operator=(star&&);

  const core::t_vec2d& CalcXY();

  double m_theta;           // position on the ellipse
  double m_velTheta;        // angular velocity
  double m_angle;           // tilt of the ellipse
  double m_a;               // minor half axis
  double m_b;               // major half axis
  double m_temp;            // star temperature
  double m_mag;             // brigtness;
  core::t_vec2d m_center;   // center of the elliptical orbit
  core::t_vec2d m_vel;      // Current velocity (calculated)
  core::t_vec2d m_pos;      // current position in kartesion koordinates
};


#endif /* INCLUDE_STAR_H_ */

