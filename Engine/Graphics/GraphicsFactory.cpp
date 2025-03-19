
module;

#include "GLogger.h"

module GraphicsFactory;


namespace lumine::graphics
{

GraphicsFactory::~GraphicsFactory()
{
	Close();
}

void GraphicsFactory::Initialize()
{
	GCREATE_LOGGER();

	m_Initialized = true;
	GTRACE("Initialized");
}

void GraphicsFactory::Close()
{
	if (not m_Initialized)
	{
		return;
	}

	m_Initialized = false;
	GTRACE("Closed");
}

}
