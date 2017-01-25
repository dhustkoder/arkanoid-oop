#version 330 core
in vec2 fs_tex_coords;

out vec4 pixel;

uniform sampler2D tex_unit;

void main()
{
    pixel = texture(tex_unit, fs_tex_coords);
}
