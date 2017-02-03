#version 330 core
layout (location = 0) in vec4 pos_and_uv;
layout (location = 1) in vec4 color;
layout (location = 2) in float tex_id;

out vec2 fs_tex_coords;
out vec4 fs_color;
out float fs_tex_id;


uniform mat4 projection;
uniform mat4 view = mat4(1.0f);
uniform mat4 model = mat4(1.0f);


void main()
{
	gl_Position = projection * view * model * vec4(pos_and_uv.xy, 0, 1);
	fs_tex_coords = vec2(pos_and_uv.zw);
	fs_color = color;
	fs_tex_id = tex_id;
}


