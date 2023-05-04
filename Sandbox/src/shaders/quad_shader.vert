#version 450 core

layout (location = 0) in vec4  position;
layout (location = 1) in vec4  in_color;
layout (location = 2) in vec2  texture_position;
layout (location = 3) in uint  texture_slot;
layout (location = 4) in float tiling_factor;

out vec4 f_color;
out vec2 f_texture_position;
out flat uint f_texture_slot;
out flat float f_tiling_factor;
uniform mat4 u_view_proj;

void main()
{
    gl_Position = u_view_proj * position;
    f_color = in_color;
    f_texture_position = texture_position;
    f_texture_slot = texture_slot;
    f_tiling_factor = tiling_factor;
}