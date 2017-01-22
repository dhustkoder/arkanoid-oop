#version 330 core

in vec4 object_color;
in vec2 fragment_tex_coords;

uniform sampler2D texture_unit;
uniform vec3 light_color;

out vec4 pixel;

void main(void)
{
//	pixel = texture(texture_unit, fragment_tex_coords) * vec4(light_source, 1) * fragment_color;
	pixel = vec4(light_color, 1) * object_color;
}

