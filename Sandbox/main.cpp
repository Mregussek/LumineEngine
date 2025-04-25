
import ToolsFactory;
import Window;
import Path;

import GraphicsFactory;
#include <memory>
#include <iostream>

using namespace lumine;
using namespace lumine::graphics;


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

		GraphicsSpecification graphicsSpecs{
			.backendType = EBackendType::Vulkan
		};
		m_GraphicsFactory.Initialize(graphicsSpecs);
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

	}

private:

	ToolsFactory m_ToolsFactory{};
	GraphicsFactory m_GraphicsFactory{};
	std::shared_ptr<Window> m_pWindow{ nullptr };

};


int main()
{
	SandboxBase sandbox{};
	sandbox.Initialize();
	sandbox.Run();
}
