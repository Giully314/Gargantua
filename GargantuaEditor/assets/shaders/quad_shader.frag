#version 450 core

out vec4 FragColor;

in vec4 f_color;
in vec2 f_texture_position;
in flat uint f_texture_slot;
in flat float f_tiling_factor;

uniform sampler2D u_textures[16];
    

void main()
{
    int idx = int(f_texture_slot);
    FragColor = texture(u_textures[idx], f_texture_position * f_tiling_factor) * f_color;
} 