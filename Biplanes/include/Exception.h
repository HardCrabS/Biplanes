#pragma once
#include <exception>
#include <string>

class Exception : public std::exception
{
public:
	Exception(const std::string& m) : message(m) {}
	virtual const char* what() const throw()
	{
		return message.c_str();
	}
private:
	std::string message{};
};