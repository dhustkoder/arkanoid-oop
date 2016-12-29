#include "shaders.hpp"

namespace gp {

constexpr const char* const kVertexShader = "#version 120\n"
"attribute vec3 position;\n"
"attribute vec2 texCoord;\n"
"attribute vec3 normal;\n"
"varying vec2 texCoord0;\n"
"varying vec3 normal0;\n"
"uniform mat4 MVP;\n"
"uniform mat4 Normal;\n"
"void main()\n"
"{\n"
"	gl_Position = MVP * vec4(position, 1.0);\n"
"	texCoord0 = texCoord;\n"
"	normal0 = (Normal * vec4(normal, 0.0)).xyz;\n"
"};\n";

constexpr const char* const kFragmentShader = "#version 120\n"
"varying vec2 texCoord0;\n"
"varying vec3 normal0;\n"
"uniform sampler2D sampler\n"
"uniform vec3 lightDirection\n"
"void main()\n"
"{\n"
"	gl_FragColor = texture2D(sampler, texCoord0) * \n"
"		clamp(dot(-lightDirection, normal0), 0.0, 1.0);\n"
"};\n";


void load_shaders()
{
	// load
}


} // namespace gp
