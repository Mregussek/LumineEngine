
module;

#include "TLogger.h"
#include <memory>

module ToolsFactory;

import WindowImplCross;
import WindowImplGlfw;


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


std::shared_ptr<Window> ToolsFactory::CreateWindow() const
{
	return std::make_shared<WindowImplGlfw>();
}

}
