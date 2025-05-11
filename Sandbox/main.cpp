
import ToolsFactory;
import IWindow;
import Path;

import GraphicsFactory;
import GraphicsSpecification;
#include <memory>
#include <iostream>

using namespace lumine;
using namespace lumine::graphics;


constexpr static EBackendType GetBackendType()
{
	if constexpr (LUMINE_USE_DIRECTX12)
	{
		return EBackendType::DirectX12;
	}
	return EBackendType::Vulkan;
}


class SandboxBase
{
public:

	void Initialize()
	{
		m_ToolsFactory.Initialize();

		Path iconPath({ "Media", "lumine.png" });
		WindowDescription windowDesc{
			.width = 1600,
			.height = 900,
			.nameId = "LumineSandboxID",
			.title = "LumineSandbox",
			.iconPath = iconPath,
			.resizable = false,
			.minimizable = false
		};
		m_pWindow = m_ToolsFactory.CreateWindow();
		m_pWindow->Create(windowDesc);

		m_GraphicsFactory.Initialize();

		m_pGraphicsApi = m_GraphicsFactory.CreateBackend(GetBackendType());

		GraphicsSpecification graphicsSpecs{};
		m_pGraphicsApi->Initialize(graphicsSpecs);
	}

	void Run()
	{
		bool isRunning = true;
		while (isRunning)
		{
			m_pWindow->Update();

			while (m_pWindow->HasPendingEvents())
			{
				WindowEvent windowEvent = m_pWindow->GetNextEvent();

				if (windowEvent.IsClose())
				{
					isRunning = false;
				}
			}
		}
	}

	void Close()
	{
		m_pGraphicsApi->Close();
		m_ToolsFactory.Close();
	}

private:

	ToolsFactory m_ToolsFactory{};
	GraphicsFactory m_GraphicsFactory{};
	std::unique_ptr<IGraphicsBackend> m_pGraphicsApi{ nullptr };
	std::shared_ptr<IWindow> m_pWindow{ nullptr };

};


int main()
{
	SandboxBase sandbox{};
	sandbox.Initialize();
	sandbox.Run();
	sandbox.Close();
}
