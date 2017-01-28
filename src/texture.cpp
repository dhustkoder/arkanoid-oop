#include <string>
#include <SOIL/SOIL.h>
#include "texture.hpp"
#include "exception.hpp"


namespace gp {

	
Texture::Texture(const char* const texture_file_path)
{
	using namespace std::string_literals;

	glGenTextures(1, &m_textureId);
	if (m_textureId == 0)
		throw Exception("failed to generate texture "s + texture_file_path);

	enable();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* const img = SOIL_load_image(texture_file_path, &m_width, &m_height, nullptr, SOIL_LOAD_RGBA);

	if (img == nullptr)
		throw Exception("Couldn't load texture "s + texture_file_path + " " + SOIL_last_result());

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(img);

	disable();
}


Texture::~Texture()
{
	glDeleteTextures(1, &m_textureId);
}


} // namespace gp

