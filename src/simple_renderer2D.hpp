#ifndef GPROJ_SIMPLE_RENDERER2D_HPP_
#define GPROJ_SIMPLE_RENDERER2D_HPP_
#include <deque>
#include "renderer2D.hpp"

namespace gp {

class SimpleRenderer2D final : public Renderer2D {
public:
	void submit(const Renderable2D* renderable) override;
	void flush() override;
private:
	std::deque<const Renderable2D*> m_renderQueue;
};


} // namespace gp
#endif

