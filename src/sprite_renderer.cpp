#include <glm/gtc/matrix_transform.hpp>
#include "display.hpp"
#include "finally.hpp"
#include "sprite_renderer.hpp"


namespace gp {

constexpr int SpriteRenderer::kTextureIndexes[SpriteRenderer::kMaxTextures];

SpriteRenderer::SpriteRenderer()
	: m_shader("../data/shaders/sprite_renderer.vs", "../data/shaders/sprite_renderer.fs"),
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

	m_shader.setUniform1iv("textures", &kTextureIndexes[0], kMaxTextures);
	m_shader.setUniformMat4("projection",
	  glm::ortho(0.0f, Display::getViewSize().x, Display::getViewSize().y,
	             0.0f, -1.0f, 1.0f));

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
		glActiveTexture(GL_TEXTURE0 + texture->getIndex());
		texture->enable();
	}


	glDrawArrays(GL_QUADS, 0, m_spriteCount * 4);


	if (is_writting_to_buffer) {
		m_bufferData = static_cast<VertexData*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
	} else {
		m_shader.disable();
		this->unbindVertexObjects();
	}

	m_spriteCount = 0;
	m_textures.clear();
}


} // namespace gp

