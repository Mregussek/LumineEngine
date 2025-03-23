
import ToolsFactory;
import Window;
import Path;

import GraphicsFactory;
#include <memory>
#include <iostream>

using namespace lumine;
using namespace lumine::graphics;

int main()
{
	ToolsFactory toolsFactory{};
	toolsFactory.Initialize();

	Path iconPath( { "Media", "lumine.png" } );

	WindowDescription windowDesc{};
	windowDesc.width = 1600;
	windowDesc.height = 900;
	windowDesc.nameId = "LumineSandboxID";
	windowDesc.title = "LumineSandbox";
	windowDesc.iconPath = iconPath;
	windowDesc.resizable = true;

	std::shared_ptr<Window> pWindow = toolsFactory.GetWindow();
	pWindow->Create(windowDesc);

	GraphicsFactory graphicsFactory{};
	graphicsFactory.Initialize();

	bool isRunning = true;
	while (isRunning)
	{
		pWindow->Update();

		while (pWindow->HasPendingEvents())
		{
			WindowEvent windowEvent = pWindow->GetNextEvent();

			if (windowEvent.IsClose())
			{
				isRunning = false;
			}
		}
	}
}
