#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "renderer/display.hpp"
#include "renderer/renderer.hpp"
#include "renderer/shaders.hpp"
#include "renderer/textures.hpp"
#include "utils/finally.hpp"
#include "math/matrix4.hpp"
#include "math/vector2.hpp"

constexpr const char* kWinTitle = "GProj";
constexpr const int kWinWidth = 1366;
constexpr const int kWinHeight = 766;

enum ShaderIds {
	kLightingShader = 0,
	kLampShader = 1
};


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

	const Vec3 kCoral { 1, 0.5f, 0.31f };
	const Vec3 kObjectPos { 0, 0, 0 };
	Vec3 light_pos { 1.2f, 1.0f, 2.0f };

	constexpr const Vertex data [] {
		// front
		{ { 0.5f, 0.5f, 0.5f }, { 0, 0, 1 } }, 
		{ { 0.5f,-0.5f, 0.5f }, { 0, 0, 1 } }, 
		{ {-0.5f,-0.5f, 0.5f }, { 0, 0, 1 } }, 
		{ {-0.5f, 0.5f, 0.5f }, { 0, 0, 1 } },

		// left 
		{ {-0.5f, 0.5f, 0.5f }, {-1, 0, 0 } },
		{ {-0.5f,-0.5f, 0.5f }, {-1, 0, 0 } },
		{ {-0.5f,-0.5f,-0.5f }, {-1, 0, 0 } },
		{ {-0.5f, 0.5f,-0.5f }, {-1, 0, 0 } },

		// back
		{ { 0.5f, 0.5f,-0.5f }, { 0, 0,-1 } },
		{ { 0.5f,-0.5f,-0.5f }, { 0, 0,-1 } },
		{ {-0.5f,-0.5f,-0.5f }, { 0, 0,-1 } },
		{ {-0.5f, 0.5f,-0.5f }, { 0, 0,-1 } },

		// right
		{ { 0.5f, 0.5f,-0.5f }, { 1, 0, 0 } },
		{ { 0.5f,-0.5f,-0.5f }, { 1, 0, 0 } },
		{ { 0.5f,-0.5f, 0.5f }, { 1, 0, 0 } },
		{ { 0.5f, 0.5f, 0.5f }, { 1, 0, 0 } },

		// up
		{ { 0.5f, 0.5f,-0.5f }, { 0, 1, 0 } },
		{ { 0.5f, 0.5f, 0.5f }, { 0, 1, 0 } },
		{ {-0.5f, 0.5f, 0.5f }, { 0, 1, 0 } },
		{ {-0.5f, 0.5f,-0.5f }, { 0, 1, 0 } },

		// down
		{ { 0.5f,-0.5f,-0.5f }, { 0,-1, 0 } },
		{ { 0.5f,-0.5f, 0.5f }, { 0,-1, 0 } },
		{ {-0.5f,-0.5f, 0.5f }, { 0,-1, 0 } },
		{ {-0.5f,-0.5f,-0.5f }, { 0,-1, 0 } }
	};

	constexpr unsigned int indices[] {
		// front
		0, 1, 3,
		2, 1, 3,

		// left
		4, 5, 7,
		6, 5, 7,

		// back
		8, 9, 11,
		10, 9, 11,

		// right
		12, 13, 15,
		14, 13, 15,

		// up
		16, 17, 19,
		18, 17, 19,

		// down
		20, 21, 23,
		22, 21, 23
	};


	const Elements elements {
		{ &data[0], sizeof(data)/sizeof(data[0]) },
		{ &indices[0], sizeof(indices)/sizeof(indices[0]) }
	};

	bind_element_buffer(register_element_buffer(elements));

	Vec2 lastcursor, newcursor;
	get_cursor_pos(&lastcursor);

	const float camera_speed = 3.0f;
	float delta_time = 0.0f;
	float last_frame = 0.0f;
	float yaw = -90;
	float pitch = 0;
	Vec3 camera_pos { 0, 2, 3 };
	Vec3 camera_front { 0, 0, -1 };


	const Mat4 projection = perspective(45.0f * (kPI/180), (float)kWinWidth / (float)kWinHeight, 0.1f, 100.0f);
	Mat4 view = look_at(camera_pos, camera_pos + camera_front, {0, 1, 0});

	bind_shader(kLampShader);
	set_shader_projection(projection);
	set_shader_view(view);
	set_shader_model(scale(translate(identity_mat4(), light_pos), {0.2f, 0.2f, 0.2f}));

	bind_shader(kLightingShader);
	set_shader_projection(projection);
	set_shader_view(view);
	set_shader_model(translate(identity_mat4(), kObjectPos));
	set_shader_object_color(kCoral);
	set_shader_light_color({1.0f, 1.0f, 1.0f});
	set_shader_light_pos(light_pos);
	set_shader_view_pos(camera_pos);


	time_t clk = time(nullptr);
	long fps = 0;

	while (update_display()) {
		clear_display({ 0, 0, 0, 1 });

		const auto glfwtime = static_cast<float>(glfwGetTime());
		delta_time = glfwtime - last_frame;
		last_frame = glfwtime;

		const float tsin = sinf(glfwtime);
		const float tcos = cosf(glfwtime);

		bool need_view_update = false;
		bool need_light_pos_update = false;

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
			camera_pos += normalize(cross(camera_front, { 0, 1, 0 })) * camspeed;
			need_view_update = true;
		} else if (is_key_pressed(GLFW_KEY_A)) {
			camera_pos -= normalize(cross(camera_front, { 0, 1, 0 })) * camspeed;
			need_view_update = true;
		}

		if (is_key_pressed(GLFW_KEY_UP)) {
			if (is_key_pressed(GLFW_KEY_RIGHT_CONTROL))
				light_pos.z += camspeed;
			else
				light_pos.y += camspeed;

			need_light_pos_update = true;
		} else if (is_key_pressed(GLFW_KEY_DOWN)) {
			if (is_key_pressed(GLFW_KEY_RIGHT_CONTROL))
				light_pos.z -= camspeed;
			else
				light_pos.y -= camspeed;

			need_light_pos_update = true;
		} if (is_key_pressed(GLFW_KEY_LEFT)) {
			light_pos.x -= camspeed;
			need_light_pos_update = true;
		} else if (is_key_pressed(GLFW_KEY_RIGHT)) {
			light_pos.x += camspeed;
			need_light_pos_update = true;
		}

		if (need_view_update) {
			view = look_at(camera_pos, camera_pos + camera_front, { 0, 1, 0 });

			bind_shader(kLightingShader);
			set_shader_view(view);
			set_shader_view_pos(camera_pos);

			bind_shader(kLampShader);
			set_shader_view(view);
		}

		if (need_light_pos_update) {
			bind_shader(kLightingShader);
			set_shader_light_pos(light_pos);

			bind_shader(kLampShader);
			Mat4 lightmodel = translate(identity_mat4(), light_pos);
			lightmodel = scale(lightmodel, {0.2f, 0.2f, 0.2f});
			set_shader_model(lightmodel);
		}

		bind_shader(kLampShader);
		draw_element_buffer(GL_TRIANGLES, 0, elements.indices.count);
		bind_shader(kLightingShader);
		draw_element_buffer(GL_TRIANGLES, 0, elements.indices.count);

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
	constexpr const char* const vertexfiles[2] { 
		"../shaders/lighting.vs",
		"../shaders/lamp.vs"
	};

	constexpr const char* const fragmentfiles[2] {
		"../shaders/lighting.fs",
		"../shaders/lamp.fs"
	};
	
	const gp::ShadersProgramsFiles shaders {
		vertexfiles,
		fragmentfiles,
		2
	};

	const gp::TexturesFiles textures {
		nullptr,
		0
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

