#version 330 core

in vec2 s_texture_coords;

out vec4 s_color;


uniform sampler2D u_texture; 

void main()
{
   s_color =  texture(u_texture, s_texture_coords);
};