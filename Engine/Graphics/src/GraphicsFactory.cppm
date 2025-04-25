
module;

#include "Types.h"
#include <memory>

export module GraphicsFactory;

import BackendFactory;


export namespace lumine::graphics
{

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

	std::unique_ptr<IBackendFactory> m_pBackendFactory{ nullptr };
	bool m_Initialized{ false };

};

}
