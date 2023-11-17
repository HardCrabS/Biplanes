#include "Logger.h"

void logInfo(const std::string& message)
{
	std::cout << message << std::endl;
}

void logError(const std::string& message)
{
	std::cerr << message << std::endl;
}
