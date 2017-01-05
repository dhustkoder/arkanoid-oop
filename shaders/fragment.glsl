#version 330 core

in vec2 fragment_tex_coords;
in vec4 fragment_color;

out vec4 pixel_color;

uniform sampler2D texture_unit;

void main(void)
{
	pixel_color = texture(texture_unit, fragment_tex_coords) * fragment_color;
}

