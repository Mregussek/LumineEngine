
#include "LoggerImpl.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <iostream>
#include <memory>
#undef ERROR


namespace lumine
{

void LoggerImpl::create(const char* loggerName)
{
	std::shared_ptr<spdlog::logger> pLogger = spdlog::stdout_color_mt(loggerName);
	pLogger->set_pattern("%^%T:[%!]:[%s:%#]>> %v%$");
	pLogger->set_level(spdlog::level::trace);
	spdlog::set_default_logger(pLogger);
}


static std::string RemoveArgsFromFunc(std::string_view sig) {
	size_t start = sig.find("__cdecl ");
	if (start != std::string_view::npos)
	{
		sig = sig.substr(start);
	}

	start = sig.find("lumine");
	if (start != std::string_view::npos)
	{
		sig = sig.substr(start);
	}
	
	size_t end = sig.find('(');
	if (end != std::string_view::npos)
	{
		sig = sig.substr(0, end);
	}

	return std::string{ sig };
}


void LoggerImpl::log(const char* loggerName, const std::string& formattedMsg, ELogLevel logLevel,
					 const char* filename, int line, const char* functionName)
{
	std::string funcNameParsed = RemoveArgsFromFunc(functionName);
	spdlog::get(loggerName)->log(spdlog::source_loc{ filename, line, funcNameParsed.data() },
								 (spdlog::level::level_enum)logLevel,
								 formattedMsg);
}

}
