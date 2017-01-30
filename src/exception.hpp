#ifndef GPROJ_EXCEPTION_HPP_
#define GPROJ_EXCEPTION_HPP_
#include <string>
#include <exception>

namespace gp {


class Exception final : public std::exception {
public:
	Exception(const std::string& msg)
		: m_msg(msg)
	{

	}

	const char* what() const noexcept override
	{
		return m_msg.c_str();
	}

private:
	std::string m_msg;
};


} // namespace gp
#endif
