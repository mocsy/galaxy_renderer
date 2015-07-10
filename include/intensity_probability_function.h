/*
 * intensity_probability_function.h
 *
 *  Created on: 09.07.2015
 *      Author: scones
 */

#ifndef INCLUDE_INTENSITY_PROBABILITY_FUNCTION_H_
#define INCLUDE_INTENSITY_PROBABILITY_FUNCTION_H_


#include <cmath>


template <class T>
class intensity_probabilty_function {

  public:

  typedef T result_type;


  intensity_probabilty_function(result_type const& galaxy_radius, result_type const& core_radius, result_type const& k = 0.02, result_type const& core_intensity = 1.0)
    :
      c_k(k),
      c_core_intensity(core_intensity),
      m_a(galaxy_radius / 3.0),
//      m_bulge_border(std::pow(c_k * galaxy_radius / 3.0, 4.0 / 3.0))
      m_bulge_border(core_radius)
  {
  }
  ~intensity_probabilty_function() = default;


  result_type operator()(result_type const& x) {
    if (x >= m_bulge_border) {
      return intensity_disc(x);
    } else {
      return intensity_bulge(x);
    }
  }


  private:


  result_type intensity_bulge(result_type const& x) {
    return c_core_intensity * std::exp(-c_k * std::pow(x, 0.25));
  }


  result_type intensity_disc(result_type const& x) {
    return c_core_intensity * std::exp(-x / m_a);
  }

  result_type const c_k;
  result_type const c_core_intensity;
  result_type m_a;
  result_type m_bulge_border;
};


#endif /* INCLUDE_INTENSITY_PROBABILITY_FUNCTION_H_ */

