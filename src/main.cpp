#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "finally.hpp"
#include "display.hpp"
#include "meshes.hpp"
#include "shader_program.hpp"


int main(int /*argc*/, char** /*argv*/)
{
	using namespace gp;

	if (!init_display("Hello gproj!", 800, 600))
		return EXIT_FAILURE;

	const auto display_guard = finally([] {
		close_display();
	});

	set_display_vsync(false);

	Vertex vertices {
		{-0.8f, -0.8f, 0.0f, 1.0f },
		{ 0.0f,  0.8f, 0.0f, 1.0f },
		{ 0.8f, -0.8f, 0.0f, 1.0f }
	};
	
	Color colors {
		{ 1.0f, 0.0f, 0.0f, 1.0f },
		{ 0.0f, 1.0f, 0.0f, 1.0f },
		{ 0.0f, 0.0f, 1.0f, 1.0f }
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

	Meshes meshes;
	if (!load_meshes(&vertices, &colors, 1, &meshes))
		return EXIT_FAILURE;

	const auto meshes_guard = finally([&meshes] {
		release_meshes(&meshes);
	});

	// just show to the screen
	long fps = 0;
	time_t start_time = time(nullptr);

	while (update_display()) {
		clear_display(0, 0.5f, 0.3f, 1);
		bind_shader_program(*shader_program);
		draw_meshes(meshes);

		++fps;
		if ((time(nullptr) - start_time) >= 1) {
			printf("FPS: %ld\n", fps);
			fps = 0;
			start_time = time(nullptr);
		}
	}

	return EXIT_SUCCESS;
}



