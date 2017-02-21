#include "display.hpp"
#include "level.hpp"

namespace gp {

Level::Level(const std::string& name, const std::string& brick_map)
	: m_name(name, {0, 0}, 2, 2)
{
	const Vec2f middle = Display::getViewSize() / 2.0f;

	m_name.setPos({middle.x - ((m_name.getRight() - m_name.getLeft()) / 2.0f),
	               middle.y - ((m_name.getBottom() - m_name.getTop()) / 2.0f)});

	m_bricks.reset(std::stoi(brick_map));
}


} // namespace gp

