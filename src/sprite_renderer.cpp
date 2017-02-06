#include <glm/gtc/matrix_transform.hpp>
#include "finally.hpp"
#include "sprite_renderer.hpp"


namespace gp {


SpriteRenderer::SpriteRenderer(Shader shader)
	: m_shader(std::move(shader)),
	m_bufferData(nullptr),
	m_spriteCount(0)
{
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);

	bindVertexObjects();
	m_shader.enable();

	const auto unbind_guard = finally([this] {
		m_shader.disable();
		unbindVertexObjects();
	});

	constexpr GLint tex_indexes[32] { 
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		10, 11, 12, 13, 14, 15, 16, 17,
		18, 19, 20, 21, 22, 23, 24, 25,
		26, 27, 28, 29, 30, 31
	};

	m_shader.setUniform1iv("textures", &tex_indexes[0], 32);
	m_shader.setUniformMat4("projection", glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f));

	glBufferData(GL_ARRAY_BUFFER, kBufferSize, nullptr, GL_DYNAMIC_DRAW);

	constexpr int attribs = 3;

	constexpr GLuint indexes[attribs] {
		kVertexPosAndUVIndex,
		kVertexColorIndex,
		kVertexTexIndexIndex 
	};

	constexpr GLint components[attribs] {
		kVertexPosAndUVComponents,
		kVertexColorComponents,
		kVertexTexIndexComponents
	};

	constexpr std::uintptr_t offsets[attribs] {
		kVertexPosAndUVOffset,
		kVertexColorOffset,
		kVertexTexIndexOffset
	};


	for (int i = 0; i < attribs; ++i) {
		glEnableVertexAttribArray(indexes[i]);
		glVertexAttribPointer(indexes[i], components[i], GL_FLOAT,
		                      GL_TRUE, kVertexDataSize, (GLvoid*)offsets[i]);
	}
}


SpriteRenderer::~SpriteRenderer()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
}


void SpriteRenderer::flush()
{
	const bool is_writting_to_buffer = m_bufferData != nullptr;

	if (is_writting_to_buffer) {
		glUnmapBuffer(GL_ARRAY_BUFFER);
	} else {
		m_shader.enable();
		this->bindVertexObjects();
	}


	for (const Texture* const texture : m_textures) {
		glActiveTexture(GL_TEXTURE0 + texture->getIndexMod());
		texture->enable();
	}


	glDrawArrays(GL_QUADS, 0, m_spriteCount * 4);


	if (is_writting_to_buffer) {
		m_bufferData = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	} else {
		m_shader.disable();
		this->unbindVertexObjects();
	}

	m_spriteCount = 0;
	m_textures.clear();
}


} // namespace gp

