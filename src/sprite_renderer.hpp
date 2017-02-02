#ifndef GPROJ_SPRITE_RENDERER_HPP_
#define GPROJ_SPRITE_RENDERER_HPP_
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include "sprite.hpp"
#include "shader.hpp"
#include "vertex_data.hpp"


namespace gp {


class SpriteRenderer {
	static constexpr const int kMaxSprites = 65000;
	static constexpr const int kVertexDataSize = sizeof(VertexData);
	static constexpr const int kSpriteSize = kVertexDataSize * 4;
	static constexpr const int kBufferSize = kSpriteSize * kMaxSprites;
public:
	SpriteRenderer(const SpriteRenderer&) = delete;
	SpriteRenderer& operator=(const SpriteRenderer&) = delete;

	SpriteRenderer(Shader&& shader);
	~SpriteRenderer();
	void submit(const Sprite* sprites, const int count);
	void flush();

private:
	void bindVertexObjects();
	void unbindVertexObjects();

	std::vector<int> m_texturesIndexes;
	Shader m_shader;
	GLuint m_vao;
	GLuint m_vbo;
	int m_spriteCount;
};


} // namespace gp
#endif

