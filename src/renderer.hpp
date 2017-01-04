#ifndef GPROJ_RENDERER_HPP_
#define GPROJ_RENDERER_HPP_
#include <vector>
#include <GL/glew.h>
#include "vectors.hpp"

namespace gp {

extern bool initialize_renderer();
extern void terminate_renderer();
extern void draw(GLenum mode,
                 const std::vector<Vec3f>& vertices,
                 const std::vector<GLuint>& indices);

}

#endif

