#include "finally.hpp"
#include "sprite_renderer.hpp"


namespace gp {


SpriteRenderer::SpriteRenderer()
	: m_vertexBuffer(kBufferSize)
{
	m_vertexBuffer.enable();
	m_vertexBuffer.registerAttribArray(kVertexPositionIndex, kVertexPositionComponents, kVertexDataSize, kVertexPositionOffset);
	m_vertexBuffer.registerAttribArray(kVertexColorIndex, kVertexColorComponents, kVertexDataSize, kVertexColorOffset);
	m_vertexBuffer.registerAttribArray(kVertexTexCoordsIndex, kVertexTexCoordsComponents, kVertexDataSize, kVertexTexCoordsOffset);
	m_vertexBuffer.disable();
}


void SpriteRenderer::submit(const Sprite* const sprites, const int count)
{
	VertexData* vertex = m_vertexBuffer.mapWriteOnlyBuffer();
	const auto unmap_guard = finally([this] {
			this->m_vertexBuffer.unmapWriteOnlyBuffer();
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

		vertex->pos = glm::vec2(left, top);
		vertex->uv = glm::vec2(0, 0);
		vertex->color = color;
		++vertex;


		vertex->pos = glm::vec2(right, top);
		vertex->uv = glm::vec2(1, 0);
		vertex->color = color;
		++vertex;

		vertex->pos = glm::vec2(right, bottom);
		vertex->uv = glm::vec2(1, 1);
		vertex->color = color;
		++vertex;

		vertex->pos = glm::vec2(left, bottom);
		vertex->uv = glm::vec2(0, 1);
		vertex->color = color;
		++vertex;
	}
}


void SpriteRenderer::flush()
{
	m_vertexBuffer.enable();
	glDrawArrays(GL_QUADS, 0, m_spriteCount * 4);
	m_vertexBuffer.disable();
	m_spriteCount = 0;
}


} // namespace gp

