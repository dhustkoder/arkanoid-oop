#ifndef GPROJ_BATCH_RENDERER2D_HPP_
#define GPROJ_BATCH_RENDERER2D_HPP_

#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include "renderer2D.hpp"
#include "index_buffer.hpp"
#include "vertex_buffer.hpp"

namespace gp {


constexpr const auto kVertexDataSize = sizeof(VertexData);
constexpr const auto kSpriteSize = kVertexDataSize * 4;
constexpr const auto kBufferSize = kSpriteSize * 100;
constexpr const auto kIndicesSize = 100 * 6;


class BatchRenderer2D final : public Renderer2D {
public:
	BatchRenderer2D();
	void begin() noexcept;
	void end() noexcept;
	void submit(const Renderable2D* renderable) override;
	void flush() override;
private:
	VertexBuffer m_vertexBuffer;
	IndexBuffer m_indexBuffer;
	VertexData* m_bufferData;
	int m_indexCount = 0;
};



} // namespace gp
#endif

