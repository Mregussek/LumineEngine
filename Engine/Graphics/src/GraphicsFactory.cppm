
module;

#include "Types.h"
#include <memory>

export module GraphicsFactory;

import GraphicsBackend;


export namespace lumine::graphics
{

enum class EBackendType
{
	Vulkan = 1,
#if LUMINE_WIN64
	DirectX12 = 2,
#endif
};


class GraphicsFactory {
public:

	ErrorStatus Initialize();

	[[nodiscard]] std::unique_ptr<IGraphicsBackend> CreateBackend(EBackendType backendType) const;

};

}
