#include <stdlib.h>
#include <stdio.h>
#include "platform/display.hpp"
#include "platform/kbd_mouse_input.hpp"
#include "renderer/renderer.hpp"
#include "renderer/textures.hpp"
#include "renderer/shaders.hpp"
#include "renderer/camera.hpp"
#include "utils/finally.hpp"
#include "math/math_utils.hpp"
#include "math/matrix4.hpp"
#include "math/vector2.hpp"



constexpr const char* const kWinTitle = "GProj";
constexpr const int kWinWidth = 1366;
constexpr const int kWinHeight = 766;


static bool initialize_systems();
static void terminate_systems();


int main(int /*argc*/, char** /*argv*/)
{
	using namespace gp;

	if (!initialize_systems())
		return EXIT_FAILURE;

	const auto systems_terminator = finally([] {
		terminate_systems();
	});

	set_vsync(false);
	
	bind_shader(0);
	
	set_shader_model(translate(identity_mat4(), {0, 0, 0}));
	reset_camera(-90, 0, 3.0f, 0.25f, { 0, 0, 4 }, { 0, 1, 0 });

	constexpr const Vertex data[] {
		{ { 1.0f, 1.0f, 0.0f }, { 1, 0 } },
		{ { 1.0f,-1.0f, 0.0f }, { 1, 1 } },
		{ {-1.0f,-1.0f, 0.0f }, { 0, 1 } },
		{ {-1.0f, 1.0f, 0.0f }, { 0, 0 } },
	};

	constexpr const unsigned int indices[] {
		0, 1, 3,
		2, 1, 3,	
	};
	

	const Elements elements {
		{ &data[0], sizeof(data) / sizeof(data[0]) },
		{ &indices[0], sizeof(indices) / sizeof(indices[0]) }
	};

	const int veo = register_element_buffer(elements);
	bind_element_buffer(veo);

	int fps = 0;
	float last_frametime = 0;
	float last_fpstime = 0;
	float delta;


	const Mat4 bkg_model = scale(identity_mat4(), { 2.25f, 1.66f, 1.0f });
	const Mat4 target_model = scale(translate(identity_mat4(), { 0, 0, 0.1f }), { 0.5f, 0.5f, 1.0f });
	bool throwing = false;

	constexpr const Vec3 star_init_pos { 0.2f, 0.0f, 4.1f };
	constexpr const Vec3 star_vel { 0.0f, 0.0f, -8.0f };
	Vec3 star_pos = star_init_pos;

	constexpr const Vec3 target_init_pos { 0.0f, 0.0f, 0.1f };
	Vec3 target_vel { 0.5f, 0.0f, 0.0f };
	Vec3 target_pos = target_init_pos;
	float star_rotation = 0.0f;

	while (update_display()) {
		clear_screen({ 0, 0, 0, 1 });

		const float frametime = static_cast<float>(glfwGetTime());
		delta = frametime - last_frametime;
		last_frametime = frametime;

		bind_texture(0);
		set_shader_model(bkg_model);
		draw_element_buffer(GL_TRIANGLES);
		

		bind_texture(1);
		target_pos += target_vel * delta;

		if (target_pos.x > 4.0f)
			target_vel.x = -target_vel.x;
		else if (target_pos.x < -4.0f)
			target_vel.x = -target_vel.x;

		set_shader_model(translate(target_model, target_pos));
		draw_element_buffer(GL_TRIANGLES);

		if (throwing) {
			bind_texture(2);
			star_pos += star_vel * delta;
			Mat4 star_model = translate(identity_mat4(), star_pos);
			star_model = rotate(star_model, radians(90), { 1, 1, 0 });
			star_model = rotate(star_model, star_rotation, { 0, 0, 1 });
			star_rotation += radians(-360) * delta;
			star_model = scale(star_model, { 0.25f, 0.25f, 0.25f });
			set_shader_model(star_model);
			draw_element_buffer(GL_TRIANGLES);

			if (star_pos.z <= 0) {
				throwing = false;
			}

		} else if (is_key_pressed(GLFW_KEY_W)) {
			throwing = true;
			star_pos = star_init_pos;
			star_rotation = 0.0f;
		}

		++fps;

		if ((frametime - last_fpstime) > 1.0f) {
			printf("FPS: %i\n", fps);
			fps = 0;
			last_fpstime = frametime;
		}
	}

	return EXIT_SUCCESS;
}


bool initialize_systems()
{
	constexpr const char* const vertexfiles[1] { 
		"../shaders/simple_tex.vs"
	};

	constexpr const char* const fragmentfiles[1] {
		"../shaders/simple_tex.fs"
	};

	constexpr const char* const texturefiles[3] {
		"background.jpg",
		"target.png",
		"star.png"
	};
	
	const gp::ShadersProgramsFiles shaders {
		vertexfiles,
		fragmentfiles,
		1
	};

	const gp::TexturesFiles textures {
		texturefiles,
		3
	};

	if (!gp::initialize_renderer(kWinTitle, kWinWidth, kWinHeight, textures, shaders))
		goto renderer_failed;

	return true;

renderer_failed:
	return false;
}


void terminate_systems()
{
	gp::terminate_renderer();
}

