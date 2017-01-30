#include "finally.hpp"
#include "batch_renderer2D.hpp"


namespace gp {


BatchRenderer2D::BatchRenderer2D() :
	m_vertexBuffer(kBufferSize)
{
	m_vertexBuffer.enable();
	m_vertexBuffer.registerAttribArray(kVertexPositionIndex, kVertexPositionComponents, kVertexDataSize, kVertexPositionOffset);
	m_vertexBuffer.registerAttribArray(kVertexColorIndex, kVertexColorComponents, kVertexDataSize, kVertexColorOffset);
	m_vertexBuffer.disable();

	GLushort* const indices = new GLushort[kIndicesSize];
	const auto indices_deleter = finally([indices] {
		delete[] indices;
	});

	for (int i = 0, offset = 0; i < kIndicesSize; i += 6, offset += 4) {
		indices[i] = offset;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;

		indices[i + 3] = offset + 2;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset;
	}

	m_indexBuffer = IndexBuffer(indices, kIndicesSize);
}


void BatchRenderer2D::begin() noexcept
{
	m_bufferData = m_vertexBuffer.mapWriteOnlyBuffer();
}


void BatchRenderer2D::end() noexcept
{
	m_vertexBuffer.unmapWriteOnlyBuffer();
}

void BatchRenderer2D::submit(const Renderable2D* renderable)
{
	const auto pos = glm::vec3(renderable->getPosition(), 0.0f);
	const auto& size = renderable->getSize();
	const auto& color = renderable->getColor();

	m_bufferData->pos = pos;
	m_bufferData->color = color;
	++m_bufferData;


	m_bufferData->pos = glm::vec3(pos.x, pos.y + size.y, pos.z);
	m_bufferData->color =  color;
	++m_bufferData;


	m_bufferData->pos = glm::vec3(pos.x + size.x, pos.y + size.y, pos.z);
	m_bufferData->color = color;
	++m_bufferData;


	m_bufferData->pos = glm::vec3(pos.x + size.x, pos.y, pos.z);
	m_bufferData->color = color;
	++m_bufferData;

	m_indexCount += 6;
}


void BatchRenderer2D::flush()
{
	m_vertexBuffer.enable();
	m_indexBuffer.enable();
	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_SHORT, 0);
	m_indexBuffer.disable();
	m_vertexBuffer.disable();
	m_indexCount = 0;
}


} // namespace gp

