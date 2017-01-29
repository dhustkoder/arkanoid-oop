#ifndef GPROJ_RENDERABLE2D_HPP_
#define GPROJ_RENDERABLE2D_HPP_
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include "index_buffer.hpp"
#include "vertex_buffer.hpp"
#include "vertex_array.hpp"
#include "shader.hpp"

namespace gp {

class Renderable2D {
public:
	Renderable2D(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color, Shader& shader);
	const glm::vec2& getPosition() const { return m_position; }
	const VertexArray& getVAO() const { return m_vertexArray; }
	const IndexBuffer& getIBO() const { return m_indexBuffer; }
	const Shader& getShader() const { return m_shader; }
	Shader& getShader() { return m_shader; }
	void prepareShader() const;
private:
	VertexArray m_vertexArray;
	IndexBuffer m_indexBuffer;
	Shader& m_shader;
	glm::vec2 m_position;
	glm::vec2 m_size;
	glm::vec4 m_color;

};

} // namespace gp
#endif

