#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;

out vec4 fs_color;

uniform mat4 projection;
uniform mat4 view = mat4(1.0f);
uniform mat4 model = mat4(1.0f);

void main()
{
	//gl_Position = projection * model * vec4(position, 1.0f);
	gl_Position = projection * view * model * vec4(position, 1.0f);
	fs_color = color;
}

