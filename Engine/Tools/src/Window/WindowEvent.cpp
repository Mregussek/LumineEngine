
module;

#include "TLogger.h"

module WindowEvent;


namespace lumine
{

bool WindowEvent::IsResize() const
{
	return m_Type == WindowEventType::RESIZE;
}

ResizeWindowEventData WindowEvent::GetResizeData() const
{
	return m_EventData.resizeData;
}

bool WindowEvent::IsClose() const
{
	return m_Type == WindowEventType::CLOSE;
}

}
