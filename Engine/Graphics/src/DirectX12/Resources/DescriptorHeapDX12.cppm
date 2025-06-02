
module;

#include <wrl/client.h>
#include <d3d12.h>

export module DescriptorHeapDX12;

using Microsoft::WRL::ComPtr;


export namespace lumine::graphics::dx12
{

class DxDescriptorHeap
{
public:

	void Create(const ComPtr<ID3D12Device10>& pDevice, D3D12_DESCRIPTOR_HEAP_TYPE type,
		UINT numDescriptors);

	[[nodiscard]] const ComPtr<ID3D12DescriptorHeap>& Handle() const { return m_pHandle; }
	[[nodiscard]] D3D12_DESCRIPTOR_HEAP_TYPE Type() const { return m_Type; }
	[[nodiscard]] UINT Num() const { return m_NumDescriptors; }

private:

	ComPtr<ID3D12DescriptorHeap> m_pHandle{ nullptr };
	D3D12_DESCRIPTOR_HEAP_TYPE m_Type{ D3D12_DESCRIPTOR_HEAP_TYPE_RTV };
	UINT m_NumDescriptors{ 0 };

};

}
