#version 330 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 texture_coords;

uniform mat4 u_proj_view;
uniform mat4 u_transform;

out vec2 s_texture_coords;

void main()
{
	gl_Position = u_proj_view * u_transform * vec4(pos, 0.0, 1.0);
	s_texture_coords = texture_coords;
};
