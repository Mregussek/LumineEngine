
#pragma once

import Logger;

#define VKCREATE_LOGGER() ::lumine::Logger::create("LumineVk")

#define VKTRACE(msg, ...) ::lumine::Logger::trace("LumineVk", msg, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define VKDEBUG(msg, ...) ::lumine::Logger::debug("LumineVk", msg, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define VKINFO(msg, ...) ::lumine::Logger::info("LumineVk", msg, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define VKWARN(msg, ...) ::lumine::Logger::warning("LumineVk", msg, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define VKERROR(msg, ...) ::lumine::Logger::error("LumineVk", msg, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define VKCRITICAL(msg, ...) ::lumine::Logger::critical("LumineVk", msg, __FILE__, __LINE__, __func__, __VA_ARGS__)
