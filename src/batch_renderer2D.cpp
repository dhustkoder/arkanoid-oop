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


void BatchRenderer2D::submit(const Renderable2D* const renderables, const int count)
{
	VertexData* buffer_data = m_vertexBuffer.mapWriteOnlyBuffer();
	const auto unmap_guard = finally([this] {
			this->m_vertexBuffer.unmapWriteOnlyBuffer();
	});

	buffer_data += 4 * (m_indexCount / 6);

	for (int i = 0; i < count; ++i) {
		const Renderable2D& renderable = renderables[i];
		const float top = renderable.getTop();
		const float right = renderable.getRight();
		const float bottom = renderable.getBottom();
		const float left = renderable.getLeft();
		const glm::vec4 color = renderable.getColor();

		buffer_data->pos = glm::vec3(left, top, 0);
		buffer_data->color = color;
		++buffer_data;


		buffer_data->pos = glm::vec3(right, top, 0);
		buffer_data->color = color;
		++buffer_data;


		buffer_data->pos = glm::vec3(right, bottom, 0);
		buffer_data->color = color;
		++buffer_data;


		buffer_data->pos = glm::vec3(left, bottom, 0);
		buffer_data->color = color;
		++buffer_data;

		m_indexCount += 6;
	}
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

