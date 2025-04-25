
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
	TTRACE("Initializing");

	TDEBUG("Initialized");
}


void ToolsFactory::Close()
{
	TDEBUG("Closed");
}


std::shared_ptr<Window> ToolsFactory::CreateWindow() const
{
	return std::make_shared<WindowImplGlfw>();
}

}
