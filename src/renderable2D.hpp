#ifndef GPROJ_RENDERABLE2D_HPP_
#define GPROJ_RENDERABLE2D_HPP_
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include "index_buffer.hpp"
#include "shader.hpp"

namespace gp {


class Renderable2D {
public:
	Renderable2D(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color);
	const glm::vec2& getPosition() const;
	const glm::vec2& getSize() const;
	const glm::vec4& getColor() const;
	void setPosition(const glm::vec2& newpos);
	void setSize(const glm::vec2& newsize);
	void setColor(const glm::vec4& newcolor);
private:
	glm::vec2 m_position;
	glm::vec2 m_size;
	glm::vec4 m_color;

};


inline const glm::vec2& Renderable2D::getPosition() const
{
	return m_position;
}


inline const glm::vec2& Renderable2D::getSize() const
{
	return m_size;
}


inline const glm::vec4& Renderable2D::getColor() const
{
	return m_color;
}


inline void Renderable2D::setPosition(const glm::vec2& newpos)
{
	m_position = newpos;
}


inline void Renderable2D::setSize(const glm::vec2& newsize)
{
	m_size = newsize;
}


inline void Renderable2D::setColor(const glm::vec4& newcolor)
{
	m_color = newcolor;
}





} // namespace gp

#endif

