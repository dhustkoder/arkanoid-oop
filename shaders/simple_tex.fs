#version 330 core
in vec2 fs_tex_coords;
in vec4 fs_color;
in float fs_tex_id;

out vec4 pixel;

uniform sampler2D textures[32];

void main()
{
	pixel = texture2D(textures[int(fs_tex_id + 0.5f)], fs_tex_coords) * fs_color;
}

