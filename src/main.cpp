#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "finally.hpp"
#include "display.hpp"
#include "shader.hpp"
#include "mesh.hpp"


int main(int /*argc*/, char** /*argv*/)
{
	using namespace gp;

	if (!init_display("Hello gproj!", 800, 600))
		return EXIT_FAILURE;

	const auto display_guard = finally([] {
		close_display();
	});

	set_display_vsync(false);

	constexpr const char* const shader_sources[] {
		"../shaders/vertex.glsl",
		"../shaders/fragment.glsl"
	};

	constexpr GLenum shader_types[] {
		GL_VERTEX_SHADER,
		GL_FRAGMENT_SHADER
	};

	Shader* const shader = create_shader(shader_sources, shader_types, 2);
	if (shader == nullptr)
		return EXIT_FAILURE;

	const auto shader_guard = finally([shader] {
		destroy_shader(shader);
	});

	bind_shader(*shader);


	const Vertex quad[] {
		{ {-0.8f,  0.8f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
		{ { 0.8f,  0.8f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
		{ {-0.8f, -0.8f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
		{ { 0.8f, -0.8f, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } }
	};

	Mesh* const mesh = create_mesh(GL_TRIANGLE_STRIP, quad, 4, 1);
	if (mesh == nullptr)
		return EXIT_FAILURE;

	const auto mesh_guard = finally([mesh] {
		destroy_mesh(mesh);
	});

	// just show to the screen
	long fps = 0;
	time_t start_time = time(nullptr);

	while (update_display()) {
		clear_display(0, 0, 0, 1);
		draw_mesh(*mesh);

		++fps;
		if ((time(nullptr) - start_time) >= 1) {
			printf("FPS: %ld\n", fps);
			fps = 0;
			start_time = time(nullptr);
		}
	}

	return EXIT_SUCCESS;
}



