#version 330 core

in vec4 object_color;
in vec2 fragment_tex_coords;

uniform sampler2D texture_unit;
uniform vec3 light_color;

out vec4 pixel;

void main(void)
{
//	pixel = texture(texture_unit, fragment_tex_coords) * vec4(light_source, 1) * fragment_color;
	float ambient_strength = 0.5f;
	vec3 ambient = ambient_strength * light_color;
	pixel = object_color * vec4(ambient, 1.0f);
}

