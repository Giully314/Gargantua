#version 450 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 tex_coords;

out vec2 f_tex_coords;

void main()
{
    gl_Position = vec4(position.x, position.y, 0.0, 1.0); 
    f_tex_coords = tex_coords;
}  