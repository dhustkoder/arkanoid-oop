#ifndef ARKANOOP_FINALLY_HPP_
#define ARKANOOP_FINALLY_HPP_
#include <utility>

namespace gp {

template<class Fn>
class Finally {
public:
	Finally(const Finally& other) = delete;
	Finally& operator=(const Finally& other) = delete;

	Finally(Fn&& fn) 
		: m_fn(std::move(fn)) 
	{
	
	}
	
	
	Finally(Finally&& other)
		: m_fn(std::move(other.m_fn))
	{
		other.abort();
	}


	~Finally()
	{
		if (!m_aborted)
			m_fn();
	}


	void abort()
	{
		m_aborted = true;
	}
private:
	Fn m_fn;
	bool m_aborted = false;
};


template<class Fn>
Finally<Fn> finally(Fn&& fn)
{
	return Finally<Fn>(std::move(fn));
}


} // namespace gp
#endif

