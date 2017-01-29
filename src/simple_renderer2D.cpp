#include "simple_renderer2D.hpp"

namespace gp {

	
void SimpleRenderer2D::submit(const Renderable2D* renderable)
{
	m_renderQueue.emplace_back(renderable);
}


void SimpleRenderer2D::flush()
{
	while (!m_renderQueue.empty()) {
		const Renderable2D& renderable = *m_renderQueue.front();
		m_renderQueue.pop_front();
		renderable.getVAO().enable();
		renderable.getIBO().enable();
		renderable.getShader().enable();
		renderable.prepareShader();

		glDrawElements(GL_TRIANGLES, renderable.getIBO().getCount(), GL_UNSIGNED_SHORT, nullptr);

		renderable.getShader().disable();
		renderable.getIBO().disable();
		renderable.getVAO().disable();
	}
}


} // namespace gp

