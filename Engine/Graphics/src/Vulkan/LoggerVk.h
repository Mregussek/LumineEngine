
#pragma once

import Logger;

#if defined(_MSC_VER)
	#define VK_FUNCTION_SIG __FUNCSIG__
#elif defined(__GNUC__) || defined(__clang__)
	#define VK_FUNCTION_SIG __PRETTY_FUNCTION__
#else
	#define VK_FUNCTION_SIG VK_FUNCTION_SIG
#endif


#define VKCREATE_LOGGER() ::lumine::Logger::create("LumineVk")

#define VKTRACE(msg, ...) ::lumine::Logger::trace("LumineVk", msg, __FILE__, __LINE__, VK_FUNCTION_SIG, __VA_ARGS__)
#define VKDEBUG(msg, ...) ::lumine::Logger::debug("LumineVk", msg, __FILE__, __LINE__, VK_FUNCTION_SIG, __VA_ARGS__)
#define VKINFO(msg, ...) ::lumine::Logger::info("LumineVk", msg, __FILE__, __LINE__, VK_FUNCTION_SIG, __VA_ARGS__)
#define VKWARN(msg, ...) ::lumine::Logger::warning("LumineVk", msg, __FILE__, __LINE__, VK_FUNCTION_SIG, __VA_ARGS__)
#define VKERROR(msg, ...) ::lumine::Logger::error("LumineVk", msg, __FILE__, __LINE__, VK_FUNCTION_SIG, __VA_ARGS__)
#define VKCRITICAL(msg, ...) ::lumine::Logger::critical("LumineVk", msg, __FILE__, __LINE__, VK_FUNCTION_SIG, __VA_ARGS__)
