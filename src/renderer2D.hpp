#ifndef GPROJ_RENDERER2D_HPP_
#define GPROJ_RENDERER2D_HPP_
#include "renderable2D.hpp"


namespace gp {

class Renderer2D {
public:
	virtual void submit(const Renderable2D* renderable) = 0;
	virtual void flush() = 0;
	virtual ~Renderer2D() = default;
};


} // namespace gp
#endif

