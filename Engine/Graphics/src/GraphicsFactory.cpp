
module;

#include "GLogger.h"
#include <memory>

module GraphicsFactory;

import GraphicsBackend;


namespace lumine::graphics
{

ErrorStatus GraphicsFactory::Initialize()
{
	GCREATE_LOGGER();
	GDEBUG("Initialized");
	return ErrorStatus::OK;
}

std::unique_ptr<IGraphicsBackend> GraphicsFactory::CreateBackend(EBackendType backendType) const
{
	if (backendType == EBackendType::DirectX12)
	{
		if constexpr (LUMINE_WIN64 and LUMINE_USE_DIRECTX12)
		{
			return std::make_unique<GraphicsBackendDX12>();
		}
		else
		{
			GERROR("DirectX12 is not supported on this platform.");
			return nullptr;
		}
	}

	return std::make_unique<GraphicsBackendVk>();
}

}
