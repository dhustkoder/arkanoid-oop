#ifndef ARKANOOP_LEVEL_HPP_
#define ARKANOOP_LEVEL_HPP_
#include <string>
#include "bricks.hpp"
#include "graphic_string.hpp"

namespace gp {


class Level {
public:
	Level(const Level&) = default;
	Level(const std::string& name, const std::string& brick_map);
	const GraphicString& getName() const;
	std::vector<Brick>& getBricks();
private:
	GraphicString m_name;
	Bricks m_bricks;
};


inline const GraphicString& Level::getName() const
{
	return m_name;
}

inline std::vector<Brick>& Level::getBricks()
{
	return m_bricks.getBricks();
}

} // namespace gp
#endif

