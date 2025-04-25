
module;

#include "GLogger.h"
#include <memory>

module GraphicsFactory;

import BackendFactory;


namespace lumine::graphics
{

constexpr std::unique_ptr<IBackendFactory> CreateBackendFactory(EBackendType backendType)
{
	if (backendType == EBackendType::Vulkan)
	{
		return std::make_unique<BackedFactoryVk>();
	}

	if (backendType == EBackendType::DirectX12)
	{

		if constexpr (LUMINE_WIN64 and LUMINE_USE_DIRECTX12)
		{
			return std::make_unique<BackendFactoryDX12>();
		}
		else
		{
			GERROR("DirectX12 is not supported on this platform.");
			return nullptr;
		}
	}
}


}


namespace lumine::graphics
{

GraphicsFactory::~GraphicsFactory()
{
	Close();
}

ErrorStatus GraphicsFactory::Initialize(GraphicsSpecification specs)
{
	GCREATE_LOGGER();

	m_pBackendFactory = CreateBackendFactory(specs.backendType);
	if (not m_pBackendFactory)
	{
		return ErrorStatus::CREATE_FAILED;
	}

	m_pBackendFactory->Initialize();

	m_Initialized = true;
	GTRACE("Initialized");
	return ErrorStatus::OK;
}

void GraphicsFactory::Close()
{
	if (not m_Initialized)
	{
		return;
	}

	m_pBackendFactory->Close();
	m_Initialized = false;
	GTRACE("Closed");
}

}
