
module;

import WindowImplCross;
import WindowImplGlfw;
#include "TLogger.h"
#include <memory>

module ToolsFactory;


namespace lumine
{

ToolsFactory::~ToolsFactory()
{
	Close();
}


void ToolsFactory::Initialize()
{
	TCREATE_LOGGER();

	TTRACE("Initialized");
}


void ToolsFactory::Close()
{
	TTRACE("Closed");
}


std::shared_ptr<Window> ToolsFactory::GetWindow() const
{
	return std::make_shared<WindowImplGlfw>();
}

}
