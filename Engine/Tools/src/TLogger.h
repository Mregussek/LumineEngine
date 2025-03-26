
#pragma once

import Logger;

#define TCREATE_LOGGER() ::lumine::Logger::create("Tools")

#define TTRACE(msg, ...) ::lumine::Logger::trace("Tools", msg, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define TDEBUG(msg, ...) ::lumine::Logger::debug("Tools", msg, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define TINFO(msg, ...) ::lumine::Logger::info("Tools", msg, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define TWARN(msg, ...) ::lumine::Logger::warning("Tools", msg, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define TERROR(msg, ...) ::lumine::Logger::error("Tools", msg, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define TCRITICAL(msg, ...) ::lumine::Logger::critical("Tools", msg, __FILE__, __LINE__, __func__, __VA_ARGS__)
