
module;

#include "LoggerDX12.h"
#include <wrl/client.h>
#include <d3d12.h>

module DescriptorHeapDX12;

using Microsoft::WRL::ComPtr;


namespace lumine::graphics::dx12
{

void DxDescriptorHeap::Create(const ComPtr<ID3D12Device10>& pDevice,
	D3D12_DESCRIPTOR_HEAP_TYPE type,
	UINT numDescriptors)
{
	DXTRACE("Creating");

	m_Type = type;
	m_NumDescriptors = numDescriptors;

	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc{
		.Type = m_Type,
		.NumDescriptors = m_NumDescriptors,
		.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE,
		.NodeMask = 0
	};

	HRESULT hr = pDevice->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(m_pHandle.ReleaseAndGetAddressOf()));
	DXASSERT(hr);

	DXDEBUG("Created");
}

}
