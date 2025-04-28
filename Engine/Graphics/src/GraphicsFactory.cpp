
module;

#include "GLogger.h"
#include <memory>

module GraphicsFactory;

import BackendInterface;


namespace lumine::graphics
{

constexpr std::unique_ptr<IBackendInterface> CreateBackendInterface(EBackendType backendType)
{
	if (backendType == EBackendType::DirectX12)
	{
		if constexpr (LUMINE_WIN64 and LUMINE_USE_DIRECTX12)
		{
			return std::make_unique<BackendInterfaceDX12>();
		}
		else
		{
			GERROR("DirectX12 is not supported on this platform.");
			return nullptr;
		}
	}

	return std::make_unique<BackedInterfaceVk>();
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
	GTRACE("Initializing");

	m_pBackend = CreateBackendInterface(specs.backendType);
	if (not m_pBackend)
	{
		return ErrorStatus::CREATE_FAILED;
	}

	m_pBackend->Initialize();

	m_Initialized = true;
	GDEBUG("Initialized");
	return ErrorStatus::OK;
}

void GraphicsFactory::Close()
{
	GTRACE("Closing");

	if (m_Initialized)
	{
		m_pBackend->Close();
	}
	
	m_Initialized = false;
	GDEBUG("Closed");
}

}
