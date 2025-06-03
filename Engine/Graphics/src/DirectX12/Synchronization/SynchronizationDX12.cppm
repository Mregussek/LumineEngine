
module;

#include <wrl/client.h>
#include <d3d12.h>

export module SynchronizationDX12;

using Microsoft::WRL::ComPtr;


namespace lumine::graphics::dx12
{

class DxFenceEvent
{
public:

	~DxFenceEvent() { Close(); }

	void Create();
	void Close();

	void Wait() const;

	[[nodiscard]] HANDLE Handle() const { return m_Handle; }

private:

	HANDLE m_Handle{ nullptr };
	bool m_bCreated{ false };

};


export class DxFence
{
public:

	void Create(const ComPtr<ID3D12Device10>& pDevice);
	void Close();

	void IncrementValue() { m_Value++; }

	void Wait(UINT64 value) const;

	[[nodiscard]] const ComPtr<ID3D12Fence1>& Handle() const { return m_pHandle; }
	[[nodiscard]] UINT64 Value() const { return m_Value; }

private:

	ComPtr<ID3D12Fence1> m_pHandle{ nullptr };
	DxFenceEvent m_DxEvent{};
	UINT64 m_Value{ 0 };

};

}
