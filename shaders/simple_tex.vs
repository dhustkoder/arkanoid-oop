#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 tex_coords;
layout (location = 2) in vec4 color;

out vec4 fs_color;
out vec2 fs_tex_coords;

uniform mat4 projection;
uniform mat4 view = mat4(1.0f);
uniform mat4 model = mat4(1.0f);


void main()
{
	gl_Position = projection * view * model * vec4(position, 0, 1);
	fs_color = color;
	fs_tex_coords = tex_coords;
}


