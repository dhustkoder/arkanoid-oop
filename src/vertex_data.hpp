#ifndef GPROJ_VERTEX_DATA_HPP_
#define GPROJ_VERTEX_DATA_HPP_
#include <cstddef>
#include <cstdint>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace gp {


struct VertexData {
	glm::vec3 pos;
	glm::vec4 color;
	glm::vec2 tex_coords;
};


constexpr const int kVertexPositionIndex = 0;
constexpr const int kVertexColorIndex = 1;
constexpr const int kVertexTexCoordsIndex = 2;
constexpr const int kVertexPositionComponents = sizeof(VertexData::pos) / sizeof(GLfloat);
constexpr const int kVertexColorComponents = sizeof(VertexData::color) / sizeof(GLfloat);
constexpr const int kVertexTexCoordsComponents = sizeof(VertexData::tex_coords) / sizeof(GLfloat);
constexpr const std::uintptr_t kVertexPositionOffset = offsetof(VertexData, pos);
constexpr const std::uintptr_t kVertexColorOffset = offsetof(VertexData, color);
constexpr const std::uintptr_t kVertexTexCoordsOffset = offsetof(VertexData, tex_coords);


} // namespace gp
#endif

