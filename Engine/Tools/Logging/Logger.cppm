
module;

#include "LoggerImpl.h"

export module Logger;


#define LOGGER_FUNC_DEF(funcName)\
template<typename... Args>\
static void funcName(const char* loggerName, const char* msg, const char* file, int line, const char* funcName, Args&&... args)\
{\
	LoggerImpl::funcName(loggerName, msg, file, line, funcName, std::forward<Args>(args)...);\
}


export namespace lumine
{

class Logger
{
public:

	static void create(const char* loggerName)
	{
		LoggerImpl::create(loggerName);
	}

	LOGGER_FUNC_DEF(trace)
	LOGGER_FUNC_DEF(debug)
	LOGGER_FUNC_DEF(info)
	LOGGER_FUNC_DEF(warning)
	LOGGER_FUNC_DEF(error)
	LOGGER_FUNC_DEF(critical)

};

} // lumine::logger
