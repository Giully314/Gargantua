#version 450

out vec4 FragColor;

uniform vec4 object_color;
uniform vec4 light_color;

void main()
{
	FragColor = object_color * light_color;
}