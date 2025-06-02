
module;

#include <wrl/client.h>
#include <d3d12.h>

export module InterfaceDX12;

using Microsoft::WRL::ComPtr;

import GraphicsSpecification;
import ContextDX12;
import CommandsDX12;
import SynchronizationDX12;


export namespace lumine::graphics::dx12
{

class InterfaceDX12 {
public:

	void Initialize(const GraphicsSpecification& specs);
	void Close();

	void Present();

private:

	void PrepareCommands();
	void WaitForPreviousFrame();

private:

	ContextDX12 m_Context{};

	DxCommandList m_DxCmdList{};
	DxFence m_DxFence{};
	DxFenceEvent m_DxFenceEvent{};
	ComPtr<ID3D12PipelineState> m_pipelineState{ nullptr };

	bool m_bInitialized{ false };

};

}
