#ifndef GPROJ_VERTEX_DATA_HPP_
#define GPROJ_VERTEX_DATA_HPP_
#include <cstddef>
#include <cstdint>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace gp {


struct VertexData {
	glm::vec2 pos;
	glm::vec2 tex_coords;
	glm::vec4 color;
	GLfloat tex_index;
};


constexpr const GLuint kVertexPositionIndex = 0;
constexpr const GLuint kVertexTexCoordsIndex = 1;
constexpr const GLuint kVertexColorIndex = 2;
constexpr const GLuint kVertexTexIdIndex = 3;
constexpr const GLint kVertexPositionComponents = sizeof(VertexData::pos) / sizeof(GLfloat);
constexpr const GLint kVertexTexCoordsComponents = sizeof(VertexData::tex_coords) / sizeof(GLfloat);
constexpr const GLint kVertexColorComponents = sizeof(VertexData::color) / sizeof(GLfloat);
constexpr const GLint kVertexTexIdComponents = sizeof(VertexData::tex_id) / sizeof(GLfloat);
constexpr const std::uintptr_t kVertexPositionOffset = offsetof(VertexData, pos);
constexpr const std::uintptr_t kVertexTexCoordsOffset = offsetof(VertexData, tex_coords);
constexpr const std::uintptr_t kVertexColorOffset = offsetof(VertexData, color);
constexpr const std::uintptr_t kVertexTexIdOffset = offsetof(VertexData, tex_id);


} // namespace gp
#endif

