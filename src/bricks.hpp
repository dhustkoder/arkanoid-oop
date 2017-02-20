#ifndef ARKANOOP_BRICKS_HPP_
#define ARKANOOP_BRICKS_HPP_
#include <vector>
#include <algorithm>
#include "sprite.hpp"

namespace gp {

class Brick : public Sprite {
public:
	Brick (int resistence = 1);
	void hit(int force = 1);
	bool isDestroyed() const;

private:
	int m_resistence;
};

inline void Brick::hit(int force)
{
	m_resistence -= force;
}


inline bool Brick::isDestroyed() const
{
	return m_resistence <= 0;
}


class Bricks {
public:
	const std::vector<Brick>& getBricks() const;
	int getDestroyedBricksCount() const;
	std::vector<Brick>& getBricks();

	void update(float dt);
	void reset(int num_lines);

private:
	void removeDestroyedBricks();
	std::vector<Brick> m_bricks;
	int m_destroyedBricks;
};


inline const std::vector<Brick>& Bricks::getBricks() const
{
	return m_bricks;
}


inline std::vector<Brick>& Bricks::getBricks()
{
	return m_bricks;
}


inline int Bricks::getDestroyedBricksCount() const
{
	return m_destroyedBricks;
}


inline void Bricks::update(float /*dt*/)
{
}

inline void Bricks::removeDestroyedBricks()
{
	const auto is_destroyed = [](const Brick& brick) {
		return brick.isDestroyed();
	};

	m_bricks.erase(std::remove_if(m_bricks.begin(), m_bricks.end(), is_destroyed), m_bricks.end());
}


}
#endif
