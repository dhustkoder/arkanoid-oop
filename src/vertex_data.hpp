#ifndef ARKANOOP_VERTEX_DATA_HPP_
#define ARKANOOP_VERTEX_DATA_HPP_
#include <cstddef>
#include <cstdint>
#include "math_types.hpp"

namespace gp {


struct VertexData {
	Vec4f pos_and_uv;
	Vec4f color;
	float tex_index;
};

constexpr const int kMaxTexIndexValue = 7;
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

