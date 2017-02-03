#ifndef GPROJ_VERTEX_DATA_HPP_
#define GPROJ_VERTEX_DATA_HPP_
#include <cstddef>
#include <cstdint>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace gp {


struct VertexData {
	glm::vec4 pos_and_uv;
	glm::vec4 color;
	GLfloat tex_index;
};


constexpr const GLuint kVertexPosAndUVIndex = 0;
constexpr const GLuint kVertexColorIndex = 1;
constexpr const GLuint kVertexTexIndexIndex = 2;
constexpr const GLint kVertexPosAndUVComponents = sizeof(VertexData::pos_and_uv) / sizeof(GLfloat);
constexpr const GLint kVertexColorComponents = sizeof(VertexData::color) / sizeof(GLfloat);
constexpr const GLint kVertexTexIndexComponents = sizeof(VertexData::tex_index) / sizeof(GLfloat);
constexpr const std::uintptr_t kVertexPosAndUVOffset = offsetof(VertexData, pos_and_uv);
constexpr const std::uintptr_t kVertexColorOffset = offsetof(VertexData, color);
constexpr const std::uintptr_t kVertexTexIndexOffset = offsetof(VertexData, tex_index);


} // namespace gp
#endif

