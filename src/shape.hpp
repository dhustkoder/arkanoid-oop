#ifndef GPROJ_SHAPE_HPP_
#define GPROJ_SHAPE_HPP_
#include <glm/vec2.hpp>

namespace gp {


class Shape {
public:
	Shape(const glm::vec2 pos, const glm::vec2 size);
	virtual ~Shape();
protected:
	glm::vec2 m_pos;
	glm::vec2 m_size;	
};


} // namespace gp
#endif

