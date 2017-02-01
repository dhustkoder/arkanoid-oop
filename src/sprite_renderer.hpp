#ifndef GPROJ_SPRITE_RENDERER_HPP_
#define GPROJ_SPRITE_RENDERER_HPP_


#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include "vertex_buffer.hpp"
#include "sprite.hpp"


namespace gp {


class SpriteRenderer {
	static constexpr const int kMaxSprites = 10000;
	static constexpr const int kVertexDataSize = sizeof(VertexData);
	static constexpr const int kSpriteSize = kVertexDataSize * 4;
	static constexpr const int kBufferSize = kSpriteSize * kMaxSprites;
public:

	SpriteRenderer();
	void submit(const Sprite* sprites, const int count);
	void flush();

private:
	VertexBuffer m_vertexBuffer;
	int m_spriteCount;
};



} // namespace gp
#endif

