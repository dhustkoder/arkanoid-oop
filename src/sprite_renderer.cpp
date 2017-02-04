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
		m_shader.disable();
		unbindVertexObjects();
	});

	constexpr GLint tex_indexes[32] { 
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		10, 11, 12, 13, 14, 15, 16, 17,
		18, 19, 20, 21, 22, 23, 24, 25,
		26, 27, 28, 29, 30, 31
	};

	m_shader.setUniformIv("textures", &tex_indexes[0], 32);
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
	m_shader.enable();
	bindVertexObjects();
	auto vertex = reinterpret_cast<VertexData*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));

	const auto unmap_guard = finally([this] {
		glUnmapBuffer(GL_ARRAY_BUFFER);
		unbindVertexObjects();
		m_shader.disable();
	});

	vertex += m_spriteCount * 4;
	m_spriteCount += count;

	for (int i = 0; i < count; ++i) {
		const Sprite& sprite = sprites[i];

		const GLfloat top = sprite.getTop();
		const GLfloat right = sprite.getRight();
		const GLfloat bottom = sprite.getBottom();
		const GLfloat left = sprite.getLeft();

		const Vec2f uv_pos = sprite.getUVPos();
		const Vec2f uv_size = sprite.getUVSize();
		const Vec4f color = sprite.getColor();

		const int tex_index = sprite.getTexture().getIndex();
		const auto found_same_index = [tex_index] (const Texture* const texture) {
			return texture->getIndex() == tex_index;
		};

		if (std::find_if(m_textures.cbegin(), m_textures.cend(), found_same_index) == m_textures.cend()) {
			if (m_textures.size() >= 32)
				this->flush();
			m_textures.push_back(&sprite.getTexture());
		}

		const GLfloat tex_indexf = static_cast<GLfloat>(sprite.getTexture().getIndexMod());

		vertex->pos_and_uv = Vec4f(left, top, uv_pos.x, uv_pos.y);
		vertex->color = color;
		vertex->tex_index = tex_indexf;
		++vertex;

		vertex->pos_and_uv = Vec4f(right, top, uv_pos.x + uv_size.x, uv_pos.y);
		vertex->color = color;
		vertex->tex_index = tex_indexf;
		++vertex;

		vertex->pos_and_uv = Vec4f(right, bottom, uv_pos.x + uv_size.x, uv_pos.y + uv_size.y);
		vertex->color = color;
		vertex->tex_index = tex_indexf;
		++vertex;

		vertex->pos_and_uv = Vec4f(left, bottom, uv_pos.x, uv_pos.y + uv_size.y);
		vertex->color = color;
		vertex->tex_index = tex_indexf;
		++vertex;
	}
}


void SpriteRenderer::flush()
{
	m_shader.enable();
	bindVertexObjects();

	const auto unbind_guard = finally([this] {
		unbindVertexObjects();
		m_shader.disable();
	});

	for (const Texture* const texture : m_textures) {
		glActiveTexture(GL_TEXTURE0 + texture->getIndexMod());
		texture->enable();
	}

	glDrawArrays(GL_QUADS, 0, m_spriteCount * 4);
	m_spriteCount = 0;
	m_textures.clear();
}


} // namespace gp

