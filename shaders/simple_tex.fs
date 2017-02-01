#version 330 core
in vec4 fs_color;
in vec2 fs_tex_coords;

out vec4 pixel;

uniform sampler2D textures[32];

void main()
{
	pixel = texture(textures[0], fs_tex_coords) * fs_color;
}

