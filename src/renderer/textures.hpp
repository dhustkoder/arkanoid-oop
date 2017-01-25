#ifndef GPROJ_TEXTURES_HPP_
#define GPROJ_TEXTURES_HPP_
#include <assert.h>
#include <GL/glew.h>
#include "renderer_types.hpp"

namespace gp {


inline void bind_texture(const int index)
{
	extern GLuint textures_ids[kMaxTextures];
	assert(index < kMaxTextures);
	glBindTexture(GL_TEXTURE_2D, textures_ids[index]);
}


inline void unbind_textures()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}


} // namespace gp
#endif
