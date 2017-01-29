#ifndef GPROJ_EXCEPTION_HPP_
#define GPROJ_EXCEPTION_HPP_
#include <string>


namespace gp {

class Exception {
public:
	Exception(const std::string& msg)
		: m_msg(msg)
	{

	}


	const std::string& what() const
	{
		return m_msg;
	}

	
private:
	std::string m_msg;
};


} // namespace gp
#endif
