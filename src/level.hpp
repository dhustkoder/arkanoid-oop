#ifndef ARKANOOP_LEVEL_HPP_
#define ARKANOOP_LEVEL_HPP_
#include <string>

#include "display.hpp"
#include "graphic_string.hpp"
#include "bricks.hpp"


namespace gp {


class Level {
public:
	Level(const std::string& name, const std::string& brick_map);
private:
	GraphicString m_name;
	Bricks m_bricks;
};


} // namespace gp
#endif
