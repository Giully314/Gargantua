#version 440 core

in vec2 s_texture_coords;

out vec4 s_color;

uniform vec4 u_color;
uniform float u_tiling_factor;
uniform sampler2D u_texture; 

void main()
{
   s_color = u_color * texture(u_texture, s_texture_coords * u_tiling_factor);
};