#include <GL/glew.h>
#include <SOIL/SOIL.h>
#include "textures.hpp"
#include "vectors.hpp"
#include "finally.hpp"

namespace gp {


std::vector<GLuint> textures_ids;
static std::vector<Vector2<int>> textures_sizes;


bool initialize_textures(const std::vector<std::string>& textures_files)
{
	auto failure_guard = finally([] {
		terminate_textures();
	});

	const auto num_textures = textures_files.size();
	textures_ids.resize(num_textures);
	textures_sizes.resize(num_textures);
	glGenTextures(num_textures, textures_ids.data());

	for (size_t i = 0; i < num_textures; ++i) {
		const auto tex_id = textures_ids[i];
		const auto& tex_file = textures_files[i];
		auto& tex_size = textures_sizes[i];

		glBindTexture(GL_TEXTURE_2D, tex_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


		unsigned char* const image =
		  SOIL_load_image(tex_file.c_str(),
		                  &tex_size.x, &tex_size.y,
		                  nullptr, SOIL_LOAD_RGB);

		if (image == nullptr) {
			fprintf(stderr, "Couldn't load texture %s\n", tex_file.c_str());
			return false;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
		             tex_size.x, tex_size.y,
			     0, GL_RGB, GL_UNSIGNED_BYTE, image);

		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	failure_guard.Abort();
	return true;
}


void terminate_textures()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(textures_ids.size(), textures_ids.data());
	textures_ids.clear();
	textures_sizes.clear();
}


} // namespace gp
