
#pragma once

import Logger;

#define GCREATE_LOGGER() ::lumine::Logger::create("Graphics")

#define GTRACE(msg, ...) ::lumine::Logger::trace("Graphics", msg, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define GDEBUG(msg, ...) ::lumine::Logger::debug("Graphics", msg, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define GINFO(msg, ...) ::lumine::Logger::info("Graphics", msg, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define GWARN(msg, ...) ::lumine::Logger::warning("Graphics", msg, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define GERROR(msg, ...) ::lumine::Logger::error("Graphics", msg, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define GCRITICAL(msg, ...) ::lumine::Logger::critical("Graphics", msg, __FILE__, __LINE__, __func__, __VA_ARGS__)
