#version 450

out vec4 FragColor;

uniform vec4 light_color;

void main()
{
	FragColor = light_color;
}