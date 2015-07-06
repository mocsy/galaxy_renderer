/*
 * types.h
 *
 *  Created on: 20.10.2013
 *      Author: scn
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <glm/glm.hpp>
#include <cinttypes>


namespace core {
  template<typename T>
  using t_vec1 = glm::tvec1<T, glm::precision::highp>;

  typedef t_vec1<double> t_vec1d;
  typedef t_vec1<float> t_vec1f;
  typedef t_vec1<std::int8_t> t_vec1i8;
  typedef t_vec1<std::uint8_t> t_vec1ui8;
  typedef t_vec1<std::uint16_t> t_vec1ui16;
  typedef t_vec1<std::int16_t> t_vec1i16;
  typedef t_vec1<std::uint32_t> t_vec1ui32;
  typedef t_vec1<std::int32_t> t_vec1i32;
  typedef t_vec1<std::uint64_t> t_vec1ui64;
  typedef t_vec1<std::int64_t> t_vec1i64;

  template<typename T>
  using t_vec2 = glm::tvec2<T, glm::precision::highp>;

  typedef t_vec2<double> t_vec2d;
  typedef t_vec2<float> t_vec2f;
  typedef t_vec2<std::int8_t> t_vec2i8;
  typedef t_vec2<std::uint8_t> t_vec2ui8;
  typedef t_vec2<std::uint16_t> t_vec2ui16;
  typedef t_vec2<std::int16_t> t_vec2i16;
  typedef t_vec2<std::uint32_t> t_vec2ui32;
  typedef t_vec2<std::int32_t> t_vec2i32;
  typedef t_vec2<std::uint64_t> t_vec2ui64;
  typedef t_vec2<std::int64_t> t_vec2i64;

  template<typename T>
  using t_vec3 = glm::tvec3<T, glm::precision::highp>;

  typedef t_vec3<double> t_vec3d;
  typedef t_vec3<float> t_vec3f;
  typedef t_vec3<std::int8_t> t_vec3i8;
  typedef t_vec3<std::uint8_t> t_vec3ui8;
  typedef t_vec3<std::uint16_t> t_vec3ui16;
  typedef t_vec3<std::int16_t> t_vec3i16;
  typedef t_vec3<std::uint32_t> t_vec3ui32;
  typedef t_vec3<std::int32_t> t_vec3i32;
  typedef t_vec3<std::uint64_t> t_vec3ui64;
  typedef t_vec3<std::int64_t> t_vec3i64;

  template<typename T>
  using t_vec4 = glm::tvec4<T, glm::precision::highp>;

  typedef t_vec4<double> t_vec4d;
  typedef t_vec4<float> t_vec4f;
  typedef t_vec4<std::int8_t> t_vec4i8;
  typedef t_vec4<std::uint8_t> t_vec4ui8;
  typedef t_vec4<std::uint16_t> t_vec4ui16;
  typedef t_vec4<std::int16_t> t_vec4i16;
  typedef t_vec4<std::uint32_t> t_vec4ui32;
  typedef t_vec4<std::int32_t> t_vec4i32;
  typedef t_vec4<std::uint64_t> t_vec4ui64;
  typedef t_vec4<std::int64_t> t_vec4i64;
}


#endif /* TYPES_H_ */

