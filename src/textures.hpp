#ifndef GPROJ_TEXTURES_HPP_
#define GPROJ_TEXTURES_HPP_
#include <vector>
#include <string>

namespace gp {

extern bool initialize_textures(const std::vector<std::string>& textures_files);
extern void terminate_textures();


inline void bind_texture(const size_t index)
{
	extern std::vector<GLuint> textures_ids;
	glBindTexture(GL_TEXTURE_2D, textures_ids[index]);
}


inline void unbind_texture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}


} // namespace gp
#endif

