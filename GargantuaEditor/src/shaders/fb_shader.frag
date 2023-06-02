#version 450 core

out vec4 FragColor;
  
in vec2 f_tex_coords;

uniform sampler2D screen_texture;

void main()
{ 
    FragColor = texture(screen_texture, f_tex_coords);
}