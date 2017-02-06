#version 120
#extension GL_ARB_explicit_attrib_location : require

in vec2 fs_tex_coords;
in vec4 fs_color;
in float fs_tex_index;

out vec4 pixel;

uniform sampler2D textures[8];

void main()
{
	int tex_index = int(fs_tex_index);
	switch (tex_index) {
		case 0: pixel = texture2D(textures[0], fs_tex_coords) * fs_color; break;
		case 1: pixel = texture2D(textures[1], fs_tex_coords) * fs_color; break;
		case 2: pixel = texture2D(textures[2], fs_tex_coords) * fs_color; break;
		case 3: pixel = texture2D(textures[3], fs_tex_coords) * fs_color; break;
		case 4: pixel = texture2D(textures[4], fs_tex_coords) * fs_color; break;
		case 5: pixel = texture2D(textures[5], fs_tex_coords) * fs_color; break;
		case 6: pixel = texture2D(textures[6], fs_tex_coords) * fs_color; break;
		case 7: pixel = texture2D(textures[7], fs_tex_coords) * fs_color; break;
	}
}

