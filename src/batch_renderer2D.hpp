#ifndef GPROJ_BATCH_RENDERER2D_HPP_
#define GPROJ_BATCH_RENDERER2D_HPP_

#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include "renderer2D.hpp"
#include "index_buffer.hpp"
#include "vertex_buffer.hpp"

namespace gp {


class BatchRenderer2D final : public Renderer2D {
	static constexpr const int kMaxSprites = 10000;
	static constexpr const int kVertexDataSize = sizeof(VertexData);
	static constexpr const int kSpriteSize = kVertexDataSize * 4;
	static constexpr const int kBufferSize = kSpriteSize * kMaxSprites;
	static constexpr const int kIndicesSize = kMaxSprites * 6;
public:

	BatchRenderer2D();
	void submit(const Renderable2D* renderables, const int count) override;
	void flush() override;

private:
	VertexBuffer m_vertexBuffer;
	IndexBuffer m_indexBuffer;
	int m_indexCount = 0;
};



} // namespace gp
#endif

