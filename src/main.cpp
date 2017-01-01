#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "finally.hpp"
#include "display.hpp"
#include "vertex.hpp"
#include "shader.hpp"


int main(int /*argc*/, char** /*argv*/)
{
	using namespace gp;

	if (!init_display("Hello gproj!", 800, 600))
		return EXIT_FAILURE;

	const auto display_guard = finally([] {
		close_display();
	});

	set_display_vsync(false);

 	const Vertex triangle {
		{ -0.8f, -0.8f, 0.0f, 1.0f },
		{  0.0f,  0.8f, 0.0f, 1.0f },
		{  0.8f, -0.8f, 0.0f, 1.0f }
	};

	const Vertex colors {
		{ 1.0f, 0.0f, 0.0f, 1.0f },
		{ 0.0f, 1.0f, 0.0f, 1.0f },
		{ 0.0f, 0.0f, 1.0f, 1.0f }
	};

	const Vertex data[] {
		triangle,
		colors,
	};

	constexpr const char* const shader_sources[] {
		"../shaders/vertex.glsl",
		"../shaders/fragment.glsl"
	};

	constexpr GLenum shader_types[] {
		GL_VERTEX_SHADER,
		GL_FRAGMENT_SHADER
	};

	ShaderProgram* const shader_program =
	  create_shader_program(shader_sources, shader_types, 2);

	if (shader_program == nullptr)
		return EXIT_FAILURE;

	const auto shader_program_guard = finally([shader_program] {
		destroy_shader_program(shader_program);
	});

	VertexArray* const vao = create_vertex_array(data, 2);

	if (vao == nullptr)
		return EXIT_FAILURE;

	const auto vao_guard = finally([vao] {
		destroy_vertex_array(vao);
	});

	// just show to the screen
	long fps = 0;
	time_t start_time = time(nullptr);

	bind_shader_program(*shader_program);

	while (update_display()) {
		clear_display(0, 0, 0, 1);
		draw_vertex_array(vao);

		++fps;
		if ((time(nullptr) - start_time) >= 1) {
			printf("FPS: %ld\n", fps);
			fps = 0;
			start_time = time(nullptr);
		}
	}

	return EXIT_SUCCESS;
}



