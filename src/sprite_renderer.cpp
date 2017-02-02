#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include "finally.hpp"
#include "sprite_renderer.hpp"


namespace gp {

	
inline void SpriteRenderer::bindVertexObjects()
{
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vao);
}


inline void SpriteRenderer::unbindVertexObjects()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


SpriteRenderer::SpriteRenderer(Shader&& shader)
	: m_shader(std::move(shader)),
	m_spriteCount(0)
{
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);

	bindVertexObjects();

	m_shader.enable();

	const auto unbind_guard = finally([this] {
//		m_shader.disable();
		unbindVertexObjects();
	});


	constexpr GLint tex_indexes[32] { 
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		10, 11, 12, 13, 14, 15, 16, 17,
		18, 19, 20, 21, 22, 23, 24, 25,
		26, 27, 28, 29, 30, 31
	};

	m_shader.setUniformMat4("projection", glm::ortho(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));
	m_shader.setUniformIv("textures", &tex_indexes[0], 32);

	glBufferData(GL_ARRAY_BUFFER, kBufferSize, nullptr, GL_DYNAMIC_DRAW);

	constexpr int attribs = 4;

	constexpr GLuint indexes[attribs] {
		kVertexPositionIndex,
		kVertexTexCoordsIndex,
		kVertexColorIndex,
		kVertexTexIndexIndex 
	};

	constexpr GLint components[attribs] {
		kVertexPositionComponents,
		kVertexTexCoordsComponents,
		kVertexColorComponents,
		kVertexTexIndexComponents
	};

	constexpr std::uintptr_t offsets[attribs] {
		kVertexPositionOffset,
		kVertexTexCoordsOffset,
		kVertexColorOffset,
		kVertexTexIndexOffset
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
	bindVertexObjects();

	auto vertex = reinterpret_cast<VertexData*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));

	const auto unmap_guard = finally([this] {
		glUnmapBuffer(GL_ARRAY_BUFFER);
		unbindVertexObjects();
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

		const int tex_index = sprite.getTexture().getIndex();
		const int tex_index_mod = tex_index % 32;

		if (std::find(m_texturesIndexes.cbegin(), m_texturesIndexes.cend(), tex_index) == m_texturesIndexes.cend()) {
			if (m_texturesIndexes.size() >= 32)
				this->flush();

			// OpenGL 3.3 only holds 32 different textures samples, so we mod it
			glActiveTexture(GL_TEXTURE0 + tex_index_mod);
			sprite.getTexture().enable();
			m_texturesIndexes.push_back(tex_index);
		}

		const GLfloat tex_indexf = static_cast<GLfloat>(tex_index_mod);

		vertex->pos = glm::vec2(left, top);
		vertex->tex_coords = glm::vec2(0, 0);
		vertex->color = color;
		vertex->tex_index = tex_indexf;
		++vertex;

		vertex->pos = glm::vec2(right, top);
		vertex->tex_coords = glm::vec2(1, 0);
		vertex->color = color;
		vertex->tex_index = tex_indexf;
		++vertex;

		vertex->pos = glm::vec2(right, bottom);
		vertex->tex_coords = glm::vec2(1, 1);
		vertex->color = color;
		vertex->tex_index = tex_indexf;
		++vertex;

		vertex->pos = glm::vec2(left, bottom);
		vertex->tex_coords = glm::vec2(0, 1);
		vertex->color = color;
		vertex->tex_index = tex_indexf;
		++vertex;
	}
}


void SpriteRenderer::flush()
{
	bindVertexObjects();
	//m_shader.enable();

	const auto unbind_guard = finally([this] {
	//	m_shader.disable();
		unbindVertexObjects();
	});

	glDrawArrays(GL_QUADS, 0, m_spriteCount * 4);
	m_spriteCount = 0;
	m_texturesIndexes.clear();
}


} // namespace gp

