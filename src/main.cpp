#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "display.hpp"
#include "renderer.hpp"
#include "finally.hpp"
#include "matrix4.hpp"
#include "vector2.hpp"


constexpr const int kWinWidth = 800;
constexpr const int kWinHeight = 600;


static gp::Vec3 process_cursor_movement(const gp::Vec2& newpos, gp::Vec2* const oldpos, float* yaw, float* pitch);
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
	bind_texture(0);

	constexpr const Vertex data[] {
		// front
		{ { 0.5f, 0.5f, 0.0f }, { 1, 0 }, { 1, 0, 0, 1 } },
		{ { 0.5f,-0.5f, 0.0f }, { 1, 1 }, { 0, 1, 0, 1 } },
		{ {-0.5f,-0.5f, 0.0f }, { 0, 1 }, { 0, 0, 1, 1 } },
		{ {-0.5f, 0.5f, 0.0f }, { 0, 0 }, { 1, 1, 0, 1 } },


		// left
		{ {-0.5f, 0.5f, 0.0f }, { 1, 0 }, { 1, 0, 0, 1 } },
		{ {-0.5f,-0.5f, 0.0f }, { 1, 1 }, { 0, 1, 0, 1 } },
		{ {-0.5f,-0.5f,-1.0f }, { 0, 1 }, { 0, 0, 1, 1 } },
		{ {-0.5f, 0.5f,-1.0f }, { 0, 0 }, { 1, 1, 0, 1 } },


		// back
		{ { 0.5f, 0.5f,-1.0f }, { 1, 0 }, { 1, 0, 0, 1 } },
		{ { 0.5f,-0.5f,-1.0f }, { 1, 1 }, { 0, 1, 0, 1 } },
		{ {-0.5f,-0.5f,-1.0f }, { 0, 1 }, { 0, 0, 1, 1 } },
		{ {-0.5f, 0.5f,-1.0f }, { 0, 0 }, { 1, 1, 0, 1 } },


		// right
		{ { 0.5f, 0.5f,-1.0f }, { 1, 0 }, { 1, 0, 0, 1 } },
		{ { 0.5f,-0.5f,-1.0f }, { 1, 1 }, { 0, 1, 0, 1 } },
		{ { 0.5f,-0.5f, 0.0f }, { 0, 1 }, { 0, 0, 1, 1 } },
		{ { 0.5f, 0.5f, 0.0f }, { 0, 0 }, { 1, 1, 0, 1 } },


		// up
		{ { 0.5f, 0.5f,-1.0f }, { 1, 0 }, { 1, 0, 0, 1 } },
		{ { 0.5f, 0.5f, 0.0f }, { 1, 1 }, { 0, 1, 0, 1 } },
		{ {-0.5f, 0.5f, 0.0f }, { 0, 1 }, { 0, 0, 1, 1 } },
		{ {-0.5f, 0.5f,-1.0f }, { 0, 0 }, { 1, 1, 0, 1 } },

		// down
		{ { 0.5f,-0.5f,-1.0f }, { 1, 0 }, { 1, 0, 0, 1 } },
		{ { 0.5f,-0.5f, 0.0f }, { 1, 1 }, { 0, 1, 0, 1 } },
		{ {-0.5f,-0.5f, 0.0f }, { 0, 1 }, { 0, 0, 1, 1 } },
		{ {-0.5f,-0.5f,-1.0f }, { 0, 0 }, { 1, 1, 0, 1 } },

		// ground
		{ { 10.0f,-0.5f,-10.0f }, { 1, 0 }, { 1, 0, 0, 1 } },
		{ { 10.0f,-0.5f, 10.0f }, { 1, 1 }, { 0, 1, 0, 1 } },
		{ {-10.0f,-0.5f, 10.0f }, { 0, 1 }, { 0, 0, 1, 1 } },
		{ {-10.0f,-0.5f,-10.0f }, { 0, 0 }, { 1, 1, 0, 1 } }
	};

	constexpr const unsigned int indices[] {
		0, 1, 3,
		2, 1, 3,
		4, 5, 7,
		6, 5, 7,
		8, 9, 11,
		10, 9, 11,
		12, 13, 15,
		14, 13, 15,
		16, 17, 19,
		18, 17, 19,
		20, 21, 23,
		22, 21, 23,
		24, 25, 27,
		26, 25, 27
	};


	const Elements elements {
		{ &data[0], sizeof(data)/sizeof(data[0]) },
		{ &indices[0], sizeof(indices)/sizeof(indices[0]) }
	};

	bind_element_buffer(register_element_buffer(elements));

	Vec2 lastcursor, newcursor;
	get_cursor_pos(&lastcursor);

	const float camera_speed = 2.0f;
	float delta_time = 0.0f;
	float last_frame = 0.0f;
	float yaw = -90;
	float pitch = 0;
	Vec3 camera_pos { 0, 0, 3 };
	Vec3 camera_front { 0, 0, -1 };

	const Mat4 projection = perspective(45.0f * (kPI/180), (float)kWinWidth / (float)kWinHeight, 0.1f, 100.0f);
	set_shader_projection(0, projection);
	const Mat4 model = translate(identity_mat4(), {0, 0, 0});
	set_shader_model(0, model);
	Mat4 view = look_at(camera_pos, camera_pos + camera_front, {0, 1, 0});
	set_shader_view(0, view);

	time_t clk = time(nullptr);
	long fps = 0;

	while (update_display()) {
		clear_display({0, 0, 0, 1});

		const auto glfwtime = static_cast<float>(glfwGetTime());
		delta_time = glfwtime - last_frame;
		last_frame = glfwtime;

		const auto tsin = sinf(glfwtime);
		const auto tcos = cosf(glfwtime);
		
		bool need_view_update = false;

		get_cursor_pos(&newcursor);
		if (newcursor != lastcursor) {
			camera_front = process_cursor_movement(newcursor, &lastcursor, &yaw, &pitch);
			need_view_update = true;
		}

		const float camspeed = camera_speed * delta_time;
	
		if (is_key_pressed(GLFW_KEY_W)) {
			camera_pos += camera_front * camspeed;
			need_view_update = true;
		} else if (is_key_pressed(GLFW_KEY_S)) {
			camera_pos -= camera_front * camspeed;
			need_view_update = true;
		} if (is_key_pressed(GLFW_KEY_D)) {
			camera_pos += normalize(cross(camera_front, {0, 1, 0})) * camspeed;
			need_view_update = true;
		} else if (is_key_pressed(GLFW_KEY_A)) {
			camera_pos -= normalize(cross(camera_front, {0, 1, 0})) * camspeed;
			need_view_update = true;
		}

		if (need_view_update) {
			camera_pos.y = 0;
			view = look_at(camera_pos, camera_pos + camera_front, {0, 1, 0});
			set_shader_view(0, view);
		}

		set_shader_light_source(0, { 1, 1, 1 });
		draw_element_buffer(GL_TRIANGLES, 0, 36);
		set_shader_light_source(0, { tsin, tcos, 0.5f });
		draw_element_buffer(GL_TRIANGLES, 36, 42);

		++fps;

		time_t clk_end = time(nullptr);
		if ((clk_end - clk) >= 1) {
			printf("FPS: %ld\n", fps);
			fps = 0;
			clk = clk_end;
		}
	}


	return EXIT_SUCCESS;
}


gp::Vec3 process_cursor_movement(const gp::Vec2& newpos, gp::Vec2* const oldpos,
                                 float* const yaw, float* const pitch)
{
	using namespace gp;

	float xoffset = newpos.x - oldpos->x;
	float yoffset = oldpos->y - newpos.y; // Reversed since y-coordinates go from bottom to left
	*oldpos = newpos;

	float sensitivity = 0.05f; // Change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	*yaw   += xoffset;
	*pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (*pitch > 89.0f)
		*pitch = 89.0f;
	if (*pitch < -89.0f)
		*pitch = -89.0f;

	const auto radians = [](float x) {
		return x * (kPI / 180);
	};

	const auto rp = radians(*pitch);
	const auto ry = radians(*yaw);

	Vec3 front;
	front.x = cosf(ry) * cosf(rp);
	front.y = sinf(rp);
	front.z = sinf(ry) * cosf(rp);
	return normalize(front);
}


bool initialize_systems()
{
	const char* const vertexfiles[1] { "../shaders/vertex.glsl" };
	const char* const fragmentfiles[1] { "../shaders/fragment.glsl" };
	const char* const texturefiles[1] { "../container.jpg" };
	
	const gp::ShadersProgramsFiles shaders {
		vertexfiles,
		fragmentfiles,
		1
	};

	const gp::TexturesFiles textures {
		texturefiles,
		1
	};

	if (!gp::initialize_display("Hello GProj", kWinWidth, kWinHeight))
		goto display_failed;
	if (!gp::initialize_renderer(textures, shaders))
		goto renderer_failed;

	return true;

renderer_failed:
	gp::terminate_display();
display_failed:
	return false;
}


void terminate_systems()
{
	gp::terminate_renderer();
	gp::terminate_display();
}

