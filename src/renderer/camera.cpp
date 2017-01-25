#include "platform/kbd_mouse_input.hpp"
#include "math/matrix4.hpp"
#include "math/vector3.hpp"
#include "math/vector2.hpp"
#include "renderer_types.hpp"
#include "shaders.hpp"
#include "camera.hpp"


namespace gp {


static Camera camera;
static Vec2 last_cursor;

static void update_view();
static void update_vectors();


void reset_camera(const int win_width, const int win_height,
                  const float speed, const float sensitivity,
		  const Vec3& pos, const Vec3& world_up)
{
	last_cursor = Vec2 {
		static_cast<float>(win_width)/2,
		static_cast<float>(win_height)/2
	};


	camera.yaw = -90;
	camera.pitch = 0;

	camera.speed = speed;
	camera.sensitivity = sensitivity;

	camera.pos = pos;
	camera.world_up = world_up;

	set_shader_projection(
	  perspective(radians(45),
	    static_cast<float>(win_width) / static_cast<float>(win_height),
	    0.1f, 100.0f));


	update_vectors();
	update_view();
}


void update_camera(const float delta)
{
	bool need_view_update = false;	
	const Vec2 cursor = get_cursor_pos();

	if (cursor != last_cursor) {
		const float sensitivity = camera.sensitivity;
		camera.yaw += (cursor.x - last_cursor.x) * sensitivity;
		camera.pitch += (last_cursor.y - cursor.y) * sensitivity;

		if (camera.pitch > 89)
			camera.pitch = 89;
		else if (camera.pitch < -89)
			camera.pitch = -89;

		if (camera.yaw > 270)
			camera.yaw = -90;
		else if (camera.yaw < -450)
			camera.yaw = -90;

		last_cursor = cursor;
		update_vectors();

		need_view_update = true;
	}


	const bool w = is_key_pressed(GLFW_KEY_W);
	const bool s = is_key_pressed(GLFW_KEY_S);
	const bool d = is_key_pressed(GLFW_KEY_D);
	const bool a = is_key_pressed(GLFW_KEY_A);

	if (w || s || d || a) {
		const float speed = camera.speed * delta;

		if (w)
			camera.pos += camera.dir * speed;
		else if (s)
			camera.pos -= camera.dir * speed;

		if (d)
			camera.pos += camera.right * speed;
		else if (a)
			camera.pos -= camera.right * speed;

		need_view_update = true;
	}

	if (need_view_update)
		update_view();
}


void update_view()
{
	set_shader_view(look_at(camera.pos, camera.pos + camera.dir, camera.up));
}


void update_vectors()
{
	const float yaw = radians(camera.yaw);
	const float pitch = radians(camera.pitch);

	const Vec3 front {
		cosf(yaw) * cosf(pitch),
		sinf(pitch),
		sinf(yaw) * cosf(pitch)
	};

	camera.dir = normalize(front);
	camera.right = normalize(cross(camera.dir, camera.world_up));
	camera.up = normalize(cross(camera.right, camera.dir));
}


}

