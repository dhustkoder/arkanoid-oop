#ifndef GPROJ_SPRITE_HPP_
#define GPROJ_SPRITE_HPP_

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include "renderable2D.hpp"
#include "texture.hpp"


namespace gp {


class Sprite : public Renderable2D {
public:
	Sprite(Texture&& texture, const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color) noexcept;
private:
	Texture m_texture;
};


} // namespace gp
#endif

