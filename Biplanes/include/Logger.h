#pragma once

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <log4cplus/initializer.h>

#define DECLARE_LOGGER									log4cplus::Logger LOGGER;
#define DEFINE_LOGGER(name)								LOGGER = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT(name));
#define LogInfo(format)									LOG4CPLUS_INFO(LOGGER, LOG4CPLUS_TEXT(format));
#define LogWarn(format)									LOG4CPLUS_WARN(LOGGER, LOG4CPLUS_TEXT(format));
#define LogError(format)								LOG4CPLUS_ERROR(LOGGER, LOG4CPLUS_TEXT(format));

class Logger
{
public:
	Logger()
	{
		log4cplus::BasicConfigurator config;
		config.configure();
	}
private:
	log4cplus::Initializer initializer;
};