#include <glm/gtc/matrix_transform.hpp>
#include "renderable2D.hpp"


namespace gp {


Renderable2D::Renderable2D(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color, Shader& shader)
	: m_shader(shader),
	m_position(pos),
	m_size(size),
	m_color(color)
{
	GLfloat vertices[] {
		0, 0, 0,
		0, size.y, 0,
		size.x, size.y, 0,
		size.x, 0, 0
	};

	GLfloat colors[] {
		color.r, color.g, color.b, color.a,
		color.r, color.g, color.b, color.a,
		color.r, color.g, color.b, color.a,
		color.r, color.g, color.b, color.a
	};

	GLushort indices[] { 0, 1, 2, 2, 3, 0 };
	m_indexBuffer = IndexBuffer(indices, sizeof(indices) / sizeof(indices[0]));
	m_vertexArray.addBuffer(vertices, 4 * 3, 3, 0);
	m_vertexArray.addBuffer(colors, 4 * 4, 4, 1);
}


void Renderable2D::prepareShader() const
{
	m_shader.setUniformMat4("model", glm::translate(glm::mat4(1), glm::vec3(m_position.x, m_position.y, 0.0f)));
}


} // namespace gp

