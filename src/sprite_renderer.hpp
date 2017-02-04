#ifndef GPROJ_SPRITE_RENDERER_HPP_
#define GPROJ_SPRITE_RENDERER_HPP_
#include <algorithm>
#include <vector>
#include "sprite.hpp"
#include "shader.hpp"
#include "vertex_data.hpp"


namespace gp {


class SpriteRenderer {
	static constexpr const int kMaxSprites = 255;
	static constexpr const int kVertexDataSize = sizeof(VertexData);
	static constexpr const int kSpriteSize = kVertexDataSize * 4;
	static constexpr const int kBufferSize = kSpriteSize * kMaxSprites;
public:
	SpriteRenderer(const SpriteRenderer&) = delete;
	SpriteRenderer& operator=(const SpriteRenderer&) = delete;

	SpriteRenderer(Shader&& shader);
	~SpriteRenderer();
	void begin();
	void submit(const Sprite& sprite);
	void end();
	void flush();

private:
	void bindVertexObjects();
	void unbindVertexObjects();

	std::vector<const Texture*> m_textures;
	Shader m_shader;
	GLuint m_vao;
	GLuint m_vbo;
	VertexData* m_bufferData;
	int m_spriteCount;
};


inline void gp::SpriteRenderer::begin()
{
	m_shader.enable();
	bindVertexObjects();
	m_bufferData = reinterpret_cast<VertexData*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
}


inline void gp::SpriteRenderer::end()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
	unbindVertexObjects();
	m_shader.disable();
}


inline void SpriteRenderer::submit(const Sprite& sprite)
{
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


} // namespace gp
#endif

