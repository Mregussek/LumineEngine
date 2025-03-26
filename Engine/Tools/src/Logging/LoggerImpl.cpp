
#include "LoggerImpl.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <memory>
#undef ERROR


namespace lumine
{

void LoggerImpl::create(const char* loggerName)
{
	std::shared_ptr<spdlog::logger> pLogger = spdlog::stdout_color_mt(loggerName);
	pLogger->set_pattern("%^%T:[%s:%#]:[%!]: %v%$");
	pLogger->set_level(spdlog::level::trace);
	spdlog::set_default_logger(pLogger);
}

void LoggerImpl::log(const char* loggerName, const std::string& formattedMsg, LogLevel logLevel,
					 const char* filename, int line, const char* functionName)
{
	spdlog::get(loggerName)->log(spdlog::source_loc{ filename, line, functionName },
								 (spdlog::level::level_enum)logLevel,
								 formattedMsg);
}

}
