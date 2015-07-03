/*
 * vectors.h
 *
 *  Created on: 29.12.2014
 *      Author: scones
 */

#ifndef INCLUDE_CORE_VECTORS_H_
#define INCLUDE_CORE_VECTORS_H_

#include <glm/glm.hpp>
#include <stdint.h>

namespace core {
  // 2D
  template<typename T>
  using t_vec2 = glm::tvec2<T, glm::precision::highp>;

  typedef t_vec2<double> t_vec2d;

  // 3D
  template<typename T>
  using t_vec3 = glm::tvec3<T, glm::precision::highp>;

  typedef t_vec3<double> t_vec3d;
}

#endif /* INCLUDE_CORE_VECTORS_H_ */

