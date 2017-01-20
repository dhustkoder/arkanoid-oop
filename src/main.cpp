#include <stdlib.h>
#include <stdio.h>
#include "display.hpp"
#include "renderer.hpp"
#include "finally.hpp"
#include "matrix4.hpp"
#include "vector2.hpp"


constexpr const int kWinWidth = 1366;
constexpr const int kWinHeight = 766;


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

	set_vsync(true);
	bind_shader(0);
	bind_texture(0);

	constexpr const Vertex data[36] {
		{ {-0.5f, -0.5f, -0.5f}, { 0.0f, 0.0f }, { 1, 0, 0, 1 } },
		{ {0.5f, -0.5f, -0.5f},  {1.0f, 0.0f},   { 0, 1, 0, 1 } },
		{ {0.5f,  0.5f, -0.5f},  {1.0f, 1.0f},   { 0, 0, 1, 1 } },
		{ {0.5f,  0.5f, -0.5f},  {1.0f, 1.0f},   { 1, 1, 0, 1 } },
		{ {-0.5f,  0.5f, -0.5f},  {0.0f, 1.0f},  { 1, 0, 0, 1 } },
		{ {-0.5f, -0.5f, -0.5f},  {0.0f, 0.0f},  { 0, 1, 0, 1 } }, 

		{ {-0.5f, -0.5f,  0.5f},  {0.0f, 0.0f},  { 1, 0, 0, 1 } },
		{ {0.5f, -0.5f,  0.5f},  {1.0f, 0.0f},   { 0, 1, 0, 1 } },
		{ {0.5f,  0.5f,  0.5f},  {1.0f, 1.0f},   { 0, 0, 1, 1 } },
		{ {0.5f,  0.5f,  0.5f},  {1.0f, 1.0f},   { 1, 1, 0, 1 } },
		{ {-0.5f,  0.5f,  0.5f},  {0.0f, 1.0f},  { 1, 0, 0, 1 } },
		{ {-0.5f, -0.5f,  0.5f},  {0.0f, 0.0f},  { 0, 1, 0, 1 } },

		{ {-0.5f,  0.5f,  0.5f},  {1.0f, 0.0f}, { 1, 0, 0, 1 } },
		{ {-0.5f,  0.5f, -0.5f},  {1.0f, 1.0f}, { 0, 1, 0, 1 } },
		{ {-0.5f, -0.5f, -0.5f},  {0.0f, 1.0f}, { 0, 0, 1, 1 } },
		{ {-0.5f, -0.5f, -0.5f},  {0.0f, 1.0f}, { 1, 1, 0, 1 } },
		{ {-0.5f, -0.5f,  0.5f}, { 0.0f, 0.0f}, { 1, 0, 0, 1 } },
		{ {-0.5f,  0.5f,  0.5f},  {1.0f, 0.0f}, { 0, 1, 0, 1 } },

		{ {0.5f,  0.5f,  0.5f},  {1.0f, 0.0f}, { 1, 0, 0, 1 } },
		{ {0.5f,  0.5f, -0.5f},  {1.0f, 1.0f}, { 0, 1, 0, 1 } },
		{ {0.5f, -0.5f, -0.5f},  {0.0f, 1.0f}, { 0, 0, 1, 1 } },
		{ {0.5f, -0.5f, -0.5f}, { 0.0f, 1.0f}, { 1, 1, 0, 1 } },
		{ {0.5f, -0.5f,  0.5f},  {0.0f, 0.0f}, { 1, 0, 0, 1 } },
		{ {0.5f,  0.5f,  0.5f},  {1.0f, 0.0f}, { 0, 1, 0, 1 } },

		{ {-0.5f, -0.5f, -0.5f},  {0.0f, 1.0f}, { 1, 0, 0, 1 }  },
		{ {0.5f, -0.5f, -0.5f},  {1.0f, 1.0f},  { 0, 1, 0, 1 } },
		{ {0.5f, -0.5f,  0.5f},  {1.0f, 0.0f},  { 0, 0, 1, 1 } },
		{ {0.5f, -0.5f,  0.5f},  {1.0f, 0.0f},  { 1, 1, 0, 1 } },
		{ {-0.5f, -0.5f,  0.5f},  {0.0f, 0.0f}, { 1, 0, 0, 1 }  },
		{ {-0.5f, -0.5f, -0.5f}, { 0.0f, 1.0f}, { 0, 1, 0, 1 }  },

		{ {-0.5f,  0.5f, -0.5f}, { 0.0f, 1.0f}, { 1, 0, 0, 1 } },
		{ {0.5f,  0.5f, -0.5f},  {1.0f, 1.0f},  { 0, 1, 0, 1 } },
		{ {0.5f,  0.5f,  0.5f},  {1.0f, 0.0f},  { 0, 0, 1, 1 } },
		{ {0.5f,  0.5f,  0.5f},  {1.0f, 0.0f},  { 1, 1, 0, 1 } },
		{ {-0.5f,  0.5f,  0.5f},  {0.0f, 0.0f}, { 1, 0, 0, 1 } },
		{ {-0.5f,  0.5f, -0.5f},  {0.0f, 1.0f}, { 0, 1, 0, 1 } }
	};

	const Vertices vertices {
		&data[0],
		sizeof(data)/sizeof(data[0])
	};

	constexpr const Vec3 positions[10] {
		{ 0.0f, 0.0f, 0.0f },
		{ 2.0f, 5.0f, -15.0f },
		{-1.5f, -2.2f, -2.5f },
		{-3.8f, -2.0f, -12.3f },
		{ 2.4f, -0.4f, -3.5f },
		{-1.7f, 3.0f, -7.5f },
		{ 1.3f, -2.0f, -2.5f },
		{ 1.5f, 2.0f, -2.5f },
		{ 1.5f, 0.2f, -1.5f },
		{-1.3f, 1.0f, -1.5f }
	};

	const Mat4 projection = perspective(45.0f * (kPI/180), (float)kWinWidth / (float)kWinHeight, 0.1f, 100.0f);
	set_uniform(0, projection, "projection");


	Vec2 lastcursor, newcursor;
	get_cursor_pos(&lastcursor);

	const float camera_speed = 2.0f;
	float delta_time = 0.0f;
	float last_frame = 0.0f;
	float yaw = -90;
	float pitch = 0;
	Vec3 camera_pos { 0, 0, 3 };
	Vec3 camera_front { 0, 0, -1 };


	while (update_display()) {
		clear_display({0.67, 0.23, 0.45, 1});

		const auto time = static_cast<float>(glfwGetTime());
		delta_time = time - last_frame;
		last_frame = time;

		get_cursor_pos(&newcursor);
		if (newcursor != lastcursor)
			camera_front = process_cursor_movement(newcursor, &lastcursor, &yaw, &pitch);

		const float camspeed = camera_speed * delta_time;
		if (is_key_pressed(GLFW_KEY_W))
			camera_pos += camera_front * camspeed;
		else if (is_key_pressed(GLFW_KEY_S))
			camera_pos -= camera_front * camspeed;
		if (is_key_pressed(GLFW_KEY_D))
			camera_pos += normalize(cross(camera_front, {0, 1, 0})) * camspeed;
		else if (is_key_pressed(GLFW_KEY_A))
			camera_pos -= normalize(cross(camera_front, {0, 1, 0})) * camspeed;

		Mat4 view = look_at(camera_pos, camera_pos + camera_front, {0, 1, 0});
		set_uniform(0, view, "view");

		for (int i = 0; i < 10; ++i) {
			Mat4 model = translate(identity_mat4(), positions[i]);
			model = rotate(model, time * i * 0.2f, {0.2f, 0.3f, 0.4f});
			set_uniform(0, model, "model");
			draw(GL_TRIANGLES, vertices);
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
	front.x = cos(ry) * cos(rp);
	front.y = sin(rp);
	front.z = sin(ry) * cos(rp);
	return normalize(front);
}


bool initialize_systems()
{
	const char* const vertexfiles[1] { "../shaders/vertex.glsl" };
	const char* const fragmentfiles[1] { "../shaders/fragment.glsl" };
	const char* const texturefiles[1] { "container.jpg" };
	
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

