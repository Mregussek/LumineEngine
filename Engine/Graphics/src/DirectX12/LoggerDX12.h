
#pragma once

import Logger;

#include <comdef.h>
#include <stdexcept>

#if defined(_MSC_VER)
	#define DX_FUNCTION_SIG __FUNCSIG__
#elif defined(__GNUC__) || defined(__clang__)
	#define DX_FUNCTION_SIG __PRETTY_FUNCTION__
#else
	#define DX_FUNCTION_SIG __func__
#endif


#define DXCREATE_LOGGER() ::lumine::Logger::create("LumineDX12")

#define DXTRACE(msg, ...) ::lumine::Logger::trace("LumineDX12", msg, __FILE__, __LINE__, DX_FUNCTION_SIG, __VA_ARGS__)
#define DXDEBUG(msg, ...) ::lumine::Logger::debug("LumineDX12", msg, __FILE__, __LINE__, DX_FUNCTION_SIG, __VA_ARGS__)
#define DXINFO(msg, ...) ::lumine::Logger::info("LumineDX12", msg, __FILE__, __LINE__, DX_FUNCTION_SIG, __VA_ARGS__)
#define DXWARN(msg, ...) ::lumine::Logger::warning("LumineDX12", msg, __FILE__, __LINE__, DX_FUNCTION_SIG, __VA_ARGS__)
#define DXERROR(msg, ...) ::lumine::Logger::error("LumineDX12", msg, __FILE__, __LINE__, DX_FUNCTION_SIG, __VA_ARGS__)
#define DXCRITICAL(msg, ...) ::lumine::Logger::critical("LumineDX12", msg, __FILE__, __LINE__, DX_FUNCTION_SIG, __VA_ARGS__)

#define DXASSERT(hr) \
{ \
	if (FAILED(hr)) \
	{ \
		_com_error comErr{ hr }; \
		std::string errStr = "DX12 Assert: " + std::string{ comErr.ErrorMessage() }; \
		DXERROR(errStr.c_str()); \
		throw std::runtime_error(errStr); \
	} \
}
