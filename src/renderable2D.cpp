#include <glm/gtc/matrix_transform.hpp>
#include "renderable2D.hpp"


namespace gp {


Renderable2D::Renderable2D(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color)
	:
	m_position(pos),
	m_size(size),
	m_color(color)
{
}


} // namespace gp

