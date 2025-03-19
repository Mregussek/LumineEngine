
module;

#include "GLogger.h"

module GraphicsFactory;


namespace lumine::graphics
{

void GraphicsFactory::Initialize()
{
	GCREATE_LOGGER();

	GTRACE("Initialized");
}

void GraphicsFactory::Close()
{
	GTRACE("Closed");
}

}
