#ifndef GPROJ_FINALLY_HPP_
#define GPROJ_FINALLY_HPP_

namespace gp {

template<class Fn>
class Finally {
public:
	Finally& operator=(const Finally&) = delete;
	Finally(const Finally&) = delete;

	Finally(Fn&& func) :
		m_func(static_cast<Fn&&>(func)), m_abort(false)
	{
	}
	
	Finally(Finally&& rhs) :
		m_func(rhs.m_func), m_abort(rhs.m_abort)
	{
		rhs.Abort();
	}
	
	~Finally()
	{
		if (!m_abort)
			m_func();
	}

	void Abort()
	{
		m_abort = true;
	}

private:
	Fn m_func;
	bool m_abort;
};


template<class Fn>
constexpr Finally<Fn> finally(Fn&& func)
{
	return {static_cast<Fn&&>(func)};
}


} // namespace gp
#endif

