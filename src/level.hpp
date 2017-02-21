#ifndef ARKANOOP_LEVEL_HPP_
#define ARKANOOP_LEVEL_HPP_
#include <string>
#include "bricks.hpp"
#include "graphic_string.hpp"

namespace gp {


class Level {
public:
	Level& operator=(const Level&);
	Level& operator=(Level&&) noexcept;

	Level(Level&&) noexcept;
	Level(const Level&);

	Level() = default;
	Level(const std::string& name, const std::string& brick_map);

	const GraphicString& getName() const;
	void setName(GraphicString gstr);

	std::vector<Brick>& getBricks();

private:
	GraphicString m_name;
	Bricks m_bricks;
};


inline Level& Level::operator=(const Level& other)
{
	m_name = other.m_name;
	m_bricks = other.m_bricks;
	return *this;
}

inline Level& Level::operator=(Level&& other) noexcept
{
	m_name = std::move(other.m_name);
	m_bricks = std::move(other.m_bricks);
	return *this;
}

inline Level::Level(const Level& other)
	: m_name(other.m_name),
	m_bricks(other.m_bricks)
{
	
}


inline Level::Level(Level&& other) noexcept
	: m_name(std::move(other.m_name)),
	m_bricks(std::move(other.m_bricks))
{

}


inline const GraphicString& Level::getName() const
{
	return m_name;
}

inline std::vector<Brick>& Level::getBricks()
{
	return m_bricks.getBricks();
}

inline void Level::setName(GraphicString gstr)
{
	m_name = std::move(gstr);
}

} // namespace gp
#endif

