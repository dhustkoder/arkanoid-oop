#ifndef ARKANOOP_SPRITE_RENDERER_HPP_
#define ARKANOOP_SPRITE_RENDERER_HPP_
#include <algorithm>
#include <vector>
#include "sprite.hpp"
#include "shader.hpp"
#include "vertex_data.hpp"
#include "graphic_string.hpp"


namespace gp {


class SpriteRenderer {
	static constexpr const int kMaxTextures = 8;
	static constexpr const int kTextureIndexes[kMaxTextures] {
		0, 1, 2, 3, 4, 5, 6, 7
	};

	static constexpr const int kMaxSprites = 1000;
	static constexpr const int kVertexDataSize = sizeof(VertexData);
	static constexpr const int kSpriteSize = kVertexDataSize * 4;
	static constexpr const int kBufferSize = kSpriteSize * kMaxSprites;
public:
	SpriteRenderer(const SpriteRenderer&) = delete;
	SpriteRenderer& operator=(const SpriteRenderer&) = delete;

	explicit SpriteRenderer();
	~SpriteRenderer();
	void begin();
	void submit(const Sprite& sprite);
	template<class RenderableType>
	void submit(const std::vector<RenderableType>& sprites);
	void submit(const GraphicString& gstr);
	void end();
	void flush();

private:
	void bindVertexObjects();
	void unbindVertexObjects();

	std::vector<const Texture*> m_textures;
	Shader m_shader;
	VertexData* m_bufferData;

	GLuint m_vao;
	GLuint m_vbo;
	int m_spriteCount;
};


inline void gp::SpriteRenderer::begin()
{
	m_shader.enable();
	bindVertexObjects();
	m_bufferData = static_cast<VertexData*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
}


inline void gp::SpriteRenderer::end()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
	unbindVertexObjects();
	m_shader.disable();
	m_bufferData = nullptr;
}


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


inline void SpriteRenderer::submit(const Sprite& sprite)
{
	const GLfloat top = sprite.getTop();
	const GLfloat right = sprite.getRight();
	const GLfloat bottom = sprite.getBottom();
	const GLfloat left = sprite.getLeft();

	const Vec2f uv_pos = sprite.getNormalizedUVPosition();
	const Vec2f uv_size = sprite.getNormalizedUVSize();
	const Vec4f color = sprite.getColor();

	const int tex_index = sprite.getTexture().getIndex();
	const auto is_same_index = [tex_index] (const Texture* const texture) {
		return texture->getIndex() == tex_index;
	};

	if (std::find_if(m_textures.cbegin(), m_textures.cend(), is_same_index) == m_textures.cend()) {
		if (m_textures.size() >= kMaxTextures)
			this->flush();
		m_textures.push_back(&sprite.getTexture());
	}

	const GLfloat tex_indexf = static_cast<GLfloat>(tex_index);

	m_bufferData->pos_and_uv = Vec4f(left, top, uv_pos.x, uv_pos.y);
	m_bufferData->color = color;
	m_bufferData->tex_index = tex_indexf;
	++m_bufferData;

	m_bufferData->pos_and_uv = Vec4f(right, top, uv_pos.x + uv_size.x, uv_pos.y);
	m_bufferData->color = color;
	m_bufferData->tex_index = tex_indexf;
	++m_bufferData;

	m_bufferData->pos_and_uv = Vec4f(right, bottom, uv_pos.x + uv_size.x, uv_pos.y + uv_size.y);
	m_bufferData->color = color;
	m_bufferData->tex_index = tex_indexf;
	++m_bufferData;

	m_bufferData->pos_and_uv = Vec4f(left, bottom, uv_pos.x, uv_pos.y + uv_size.y);
	m_bufferData->color = color;
	m_bufferData->tex_index = tex_indexf;
	++m_bufferData;

	++m_spriteCount;
}


template<class RenderableType>
inline void SpriteRenderer::submit(const std::vector<RenderableType>& sprites)
{
	for (const RenderableType& renderable : sprites)
		this->submit(renderable);
}

inline void SpriteRenderer::submit(const GraphicString& gstr)
{
	this->submit(gstr.getSprites());
}

} // namespace gp
#endif


