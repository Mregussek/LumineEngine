
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

	void UpdateValue();

	bool IsSubmittedWorkCompleted() const;

	void Wait() const;

	[[nodiscard]] const ComPtr<ID3D12Fence1>& Handle() const { return m_pHandle; }
	[[nodiscard]] UINT64 GetAvailableValue() const { return m_ValueAvailable; }
	[[nodiscard]] UINT64 GetSubmittedValue() const { return m_ValueSubmitted; }

private:

	ComPtr<ID3D12Fence1> m_pHandle{ nullptr };
	DxFenceEvent m_DxEvent{};
	UINT64 m_ValueAvailable{ 0 };
	UINT64 m_ValueSubmitted{ 0 };

};

}
