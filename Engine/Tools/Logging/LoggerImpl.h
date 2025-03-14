
#pragma once


#include <string>
#include <format>


#define LOGGERIMPL_FUNCTION_DEFINITION(func_name, log_level)\
template<typename... Args>\
static void func_name(const char* loggerName, const char* msg,\
					  const char* filename, int line, const char* functionName, Args&&... args)\
{\
	std::string msgStr = std::vformat(msg, std::make_format_args(std::forward<Args>(args)...));\
	log(loggerName, msgStr, log_level, filename, line, functionName);\
}


namespace lumine
{

class LoggerImpl
{

	enum class LogLevel : int
	{
		TRACE = 0,
		DEBUG = 1,
		INFO = 2,
		WARN = 3,
		ERR = 4,
		CRIT = 5
	};

public:

	static void create(const char* loggerName);

	LOGGERIMPL_FUNCTION_DEFINITION(trace, LogLevel::TRACE)
	LOGGERIMPL_FUNCTION_DEFINITION(debug, LogLevel::DEBUG)
	LOGGERIMPL_FUNCTION_DEFINITION(info, LogLevel::INFO)
	LOGGERIMPL_FUNCTION_DEFINITION(warning, LogLevel::WARN)
	LOGGERIMPL_FUNCTION_DEFINITION(error, LogLevel::ERR)
	LOGGERIMPL_FUNCTION_DEFINITION(critical, LogLevel::CRIT)

private:

	static void log(const char* loggerName, const std::string& formattedMsg, LogLevel logLevel, const char* filename, int line, const char* functionName);

};

} // lumine
