#include <stdlib.h>
#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "display.hpp"
#include "renderer.hpp"
#include "finally.hpp"
#include "matrix4.hpp"
#include "vector2.hpp"

namespace gp {
	extern GLFWwindow* window;
}

using namespace gp;


constexpr const int kWinWidth = 1366;
constexpr const int kWinHeight = 768;

float yaw = -90;
float pitch = 0;
Vec3 camera_front { 0, 0, -1 };
Vec3 camera_pos { 0, 0, 3 };
Vec3 cameta_up { 0, 1, 0 };
Vec2 cursor;


void mouse_callback(GLFWwindow* win, double xpos, double ypos);
static bool initialize_systems();
static void terminate_systems();


int main(int /*argc*/, char** /*argv*/)
{

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

	const auto tom = [] (const glm::mat4& gm) {
		Mat4 m;
		
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				m[i][j] = gm[i][j];

		return m;

	};

	const auto togm = [] (const Mat4& m) {
		glm::mat4 gm;
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				gm[i][j] = m[i][j];

		return gm;

	};

	const auto togv = [] (const Vec3& v) {
		return glm::vec3 { v.x, v.y, v.z };
	};
	const auto tov = [] (const glm::vec3& gv) {
		return Vec3 { gv.x,  gv.y, gv.z };
	};
	


	get_cursor_pos(&cursor);

	glfwSetCursorPosCallback(window, &mouse_callback);

	while (update_display()) {
		clear_display({0, 0, 0, 1});

		const auto time = static_cast<float>(glfwGetTime());
		const auto tsin = sinf(time * 3) * 0.7f;
		const auto tcos = cosf(time * 3) * 0.7f;
//		const glm::mat4 view = glm::lookAt(togv(camera_pos), togv(camera_front), glm::vec3{0, 1, 0});
//		set_uniform(0, tom(view), "view");
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



void mouse_callback(GLFWwindow* win, double xpos, double ypos)
{
	GLfloat xoffset = xpos - cursor.x;
	GLfloat yoffset = cursor.y - ypos; // Reversed since y-coordinates go from bottom to left
	cursor = Vec2 { (float)xpos, (float)ypos };

	GLfloat sensitivity = 0.05;	// Change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw   += xoffset;
	pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	const auto radians = [](float x) {
		return x * (kPI / 180);
	};

	Vec3 front;
	front.x = cos(radians(yaw)) * cos(radians(pitch));
	front.y = sin(radians(pitch));
	front.z = sin(radians(yaw)) * cos(radians(pitch));
	camera_front = normalize(front);
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

