#include <utility>
#include "sprite.hpp"

namespace gp {

	
Sprite::Sprite(Texture&& texture, const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color) noexcept
	: m_texture(std::move(texture)), m_pos(pos), m_size(size), m_color(color)
{

	m_texture.enable();
}


} // namespace gp

