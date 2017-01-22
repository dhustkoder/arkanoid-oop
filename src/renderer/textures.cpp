#include <stdio.h>
#include <GL/glew.h>
#include <SOIL/SOIL.h>
#include "textures.hpp"


namespace gp {

GLuint textures_ids[kMaxTextures] { 0 };

bool create_textures(const TexturesFiles& textures_files)
{
	const int num_textures = textures_files.count;

	if (num_textures > kMaxTextures) {
		fprintf(stderr, "Max textures: %i\n", kMaxTextures);
		return false;
	}

	glGenTextures(num_textures, textures_ids);

	for (int i = 0; i < num_textures; ++i) {
		const auto tex_id = textures_ids[i];
		const char* const tex_file = textures_files.files[i];

		glBindTexture(GL_TEXTURE_2D, tex_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height;
		unsigned char* const image = SOIL_load_image(tex_file,
                                                             &width, &height,
		                                             nullptr, SOIL_LOAD_RGB);

		if (image == nullptr) {
			fprintf(stderr, "Couldn't load texture \'%s\' %s\n", tex_file, SOIL_last_result());
			return false;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	return true;
}


void free_textures()
{
	unbind_textures();
	glDeleteTextures(kMaxTextures, textures_ids);
}


}