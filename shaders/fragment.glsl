#version 330 core

in vec4 fragment_color;
in vec2 fragment_tex_coords;

uniform sampler2D texture_unit;
uniform vec3 light_source;

out vec4 pixel_color;

void main(void)
{
	pixel_color = texture(texture_unit, fragment_tex_coords) * vec4(light_source, 1) * fragment_color;
}

