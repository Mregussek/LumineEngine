
module;

#include "Types.h"
#include <memory>

export module GraphicsFactory;

import BackendInterface;


export namespace lumine::graphics
{

enum class EBackendType
{
	Vulkan = 1,
#if LUMINE_WIN64
	DirectX12 = 2,
#endif
};

struct GraphicsSpecification
{
	EBackendType backendType{ EBackendType::Vulkan };
};


class GraphicsFactory {
public:

	~GraphicsFactory();

public:

	ErrorStatus Initialize(GraphicsSpecification specs);
	void Close();

private:

	std::unique_ptr<IBackendInterface> m_pBackend{ nullptr };
	bool m_Initialized{ false };

};

}
