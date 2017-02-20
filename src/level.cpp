#include "level.hpp"

namespace gp {

Level::Level(const std::string& name, const std::string& brick_map)
	: m_name(name)
{
	m_bricks.reset(std::stoi(brick_map));
}


} // namespace gp

