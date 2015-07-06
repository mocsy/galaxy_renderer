#version 430 core
layout(location = 1) in vec4 polar_star_position;
layout(location = 2) in vec3 star_attributes;

out vec4 star_position;
out vec3 attributes;
out vec4 star_coord;

uniform mat4 world_matrix;
uniform float time;
uniform float pi;

vec2 convert_coordinates(vec2 radius, float theta, float angle) {
  float beta  = -angle;
  float alpha =  theta;

  float cos_alpha = cos(alpha);
  float sin_alpha = sin(alpha);
  float cos_beta  = cos(beta);
  float sin_beta  = sin(beta);

  return vec2(
  	radius.x * cos_beta * cos_alpha - radius.y * sin_beta * sin_alpha,
  	radius.x * sin_beta * cos_alpha + radius.y * cos_beta * sin_alpha
  );
}


void main() {
  float theta = polar_star_position.z  + (star_attributes.x/10000.0) * time;
  if (theta > 2 * pi) {
    theta -= 2 * pi;
  }
  vec4 coord = vec4(convert_coordinates(polar_star_position.xy, theta, polar_star_position.w), 2.0, 1.0);
//  vec4 coord = vec4(polar_star_position.z);
  gl_Position = world_matrix * coord;

  star_position = polar_star_position;
  attributes = star_attributes;
}

