#ifndef GPROJ_RENDERER_HPP_
#define GPROJ_RENDERER_HPP_
#include <vector>
#include <GL/glew.h>
#include "vector2.hpp"
#include "color.hpp"

namespace gp {

extern bool initialize_renderer();
extern void terminate_renderer();
extern void draw_sprites();

extern std::vector<GLuint> add_sprites(const Vec2* positions,
                                       const Vec2* sizes,
			               const Color* colors,
		 	               const bool* dynamics,
			               long count);
}

#endif

