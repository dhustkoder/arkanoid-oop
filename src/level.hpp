#ifndef ARKANOOP_LEVEL_HPP_
#define ARKANOOP_LEVEL_HPP_
#include <string>
#include "bricks.hpp"
#include "graphic_string.hpp"

namespace gp {


class Level {
public:
	Level(const std::string& name, const std::string& brick_map);
	const GraphicString& getName() const;
	Bricks& getBricks();
private:
	GraphicString m_name;
	Bricks m_bricks;
};


inline const GraphicString& Level::getName() const
{
	return m_name;
}

inline Bricks& Level::getBricks()
{
	return m_bricks;
}

} // namespace gp
#endif

