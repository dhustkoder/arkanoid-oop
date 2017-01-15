#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 tex_coords;
layout (location = 2) in vec4 color;

out vec4 fragment_color;
out vec2 fragment_tex_coords;

uniform mat4 transform;

void main(void)
{
	gl_Position = transform * vec4(position, 0.0f, 1.0f);
	fragment_color = color;
	fragment_tex_coords = tex_coords;
}

