#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 tex_coords;
layout (location = 2) in vec4 color;

out vec4 fragment_color;
out vec2 fragment_tex_coords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(void)
{
	gl_Position = projection * view * model * vec4(position, 1.0f);
	fragment_color = vec4(1, 1, 1, 1); //color;
	fragment_tex_coords = tex_coords;
}

