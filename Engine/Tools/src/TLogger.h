
#pragma once

import Logger;

#if defined(_MSC_VER)
	#define TOOLS_FUNCTION_SIG __FUNCSIG__
#elif defined(__GNUC__) || defined(__clang__)
	#define TOOLS_FUNCTION_SIG __PRETTY_FUNCTION__
#else
	#define TOOLS_FUNCTION_SIG VK_FUNCTION_SIG
#endif


#define TCREATE_LOGGER() ::lumine::Logger::create("Tools")

#define TTRACE(msg, ...) ::lumine::Logger::trace("Tools", msg, __FILE__, __LINE__, TOOLS_FUNCTION_SIG, __VA_ARGS__)
#define TDEBUG(msg, ...) ::lumine::Logger::debug("Tools", msg, __FILE__, __LINE__, TOOLS_FUNCTION_SIG, __VA_ARGS__)
#define TINFO(msg, ...) ::lumine::Logger::info("Tools", msg, __FILE__, __LINE__, TOOLS_FUNCTION_SIG, __VA_ARGS__)
#define TWARN(msg, ...) ::lumine::Logger::warning("Tools", msg, __FILE__, __LINE__, TOOLS_FUNCTION_SIG, __VA_ARGS__)
#define TERROR(msg, ...) ::lumine::Logger::error("Tools", msg, __FILE__, __LINE__, TOOLS_FUNCTION_SIG, __VA_ARGS__)
#define TCRITICAL(msg, ...) ::lumine::Logger::critical("Tools", msg, __FILE__, __LINE__, TOOLS_FUNCTION_SIG, __VA_ARGS__)
