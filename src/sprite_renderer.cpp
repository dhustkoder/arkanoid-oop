#include <glm/gtc/matrix_transform.hpp>
#include "finally.hpp"
#include "sprite_renderer.hpp"


namespace gp {


SpriteRenderer::SpriteRenderer(Shader&& shader, std::vector<Texture>&& textures)
	: m_textures(std::move(textures)),
	m_shader(std::move(shader)),
	m_spriteCount(0)
{
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vao);

	m_shader.enable();

	const auto unbind_guard = finally([this] {
		m_shader.disable();
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	});


	constexpr GLint tex_ids[32] { 
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		10, 11, 12, 13, 14, 15, 16, 17,
		18, 19, 20, 21, 22, 23, 24, 25,
		26, 27, 28, 29, 30, 31
	};

	m_shader.setUniformMat4("projection", glm::ortho(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));
	m_shader.setUniformIv("textures", tex_ids, 32);

	for (decltype(m_textures)::size_type i = 0; i < m_textures.size(); ++i) {
		glActiveTexture(GL_TEXTURE0 + i);
		m_textures[i].enable();
	}

	glBufferData(GL_ARRAY_BUFFER, kBufferSize, nullptr, GL_DYNAMIC_DRAW);

	constexpr int attribs = 4;

	constexpr GLuint indexes[attribs] {
		kVertexPositionIndex,
		kVertexTexCoordsIndex,
		kVertexColorIndex,
		kVertexTexIdIndex 
	};

	constexpr GLint components[attribs] {
		kVertexPositionComponents,
		kVertexTexCoordsComponents,
		kVertexColorComponents,
		kVertexTexIdComponents
	};

	constexpr std::uintptr_t offsets[attribs] {
		kVertexPositionOffset,
		kVertexTexCoordsOffset,
		kVertexColorOffset,
		kVertexTexIdOffset
	};


	for (int i = 0; i < attribs; ++i) {
		glEnableVertexAttribArray(indexes[i]);
		glVertexAttribPointer(indexes[i], components[i], GL_FLOAT, GL_FALSE, kVertexDataSize, (GLvoid*)offsets[i]);
	}
}


SpriteRenderer::~SpriteRenderer()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
}


void SpriteRenderer::submit(const Sprite* const sprites, const int count)
{
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	auto vertex = reinterpret_cast<VertexData*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));

	const auto unmap_guard = finally([] {
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	});

	vertex += m_spriteCount * 4;
	m_spriteCount += count;

	for (int i = 0; i < count; ++i) {
		const Sprite& sprite = sprites[i];
		const GLfloat top = sprite.getTop();
		const GLfloat right = sprite.getRight();
		const GLfloat bottom = sprite.getBottom();
		const GLfloat left = sprite.getLeft();
		const glm::vec4 color = sprite.getColor();
		const GLfloat tex_id = (GLfloat) sprite.getTextureId();

		vertex->pos = glm::vec2(left, top);
		vertex->tex_coords = glm::vec2(0, 0);
		vertex->color = color;
		vertex->tex_id = tex_id;
		++vertex;


		vertex->pos = glm::vec2(right, top);
		vertex->tex_coords = glm::vec2(1, 0);
		vertex->color = color;
		vertex->tex_id = tex_id;
		++vertex;

		vertex->pos = glm::vec2(right, bottom);
		vertex->tex_coords = glm::vec2(1, 1);
		vertex->color = color;
		vertex->tex_id = tex_id;
		++vertex;

		vertex->pos = glm::vec2(left, bottom);
		vertex->tex_coords = glm::vec2(0, 1);
		vertex->color = color;
		vertex->tex_id = tex_id;
		++vertex;
	}
}


void SpriteRenderer::flush()
{
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	m_shader.enable();

	const auto unbind_guard = finally([this] {
		m_shader.disable();
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	});

	glDrawArrays(GL_QUADS, 0, m_spriteCount * 4);
	m_spriteCount = 0;
}


} // namespace gp

