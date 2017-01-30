#ifndef GPROJ_VERTEX_DATA_HPP_
#define GPROJ_VERTEX_DATA_HPP_
#include <cstddef>
#include <cstdint>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace gp {


struct VertexData {
	glm::vec3 pos;
	glm::vec4 color;
};

constexpr const int kVertexPositionIndex = 0;
constexpr const int kVertexColorIndex = 1;
constexpr const int kVertexPositionComponents = sizeof(VertexData::pos) / sizeof(GLfloat);
constexpr const int kVertexColorComponents = sizeof(VertexData::color) / sizeof(GLfloat);
constexpr const auto kVertexPositionOffset = static_cast<std::uintptr_t>(offsetof(VertexData, pos));
constexpr const auto kVertexColorOffset = static_cast<std::uintptr_t>(offsetof(VertexData, color));

} // namespace gp
#endif

