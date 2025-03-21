
module;

#include "TLogger.h"
#include "CrossWindow/CrossWindow.h"
import WindowEvent;

module WindowImplCross;


namespace lumine
{

WindowImplCross::~WindowImplCross()
{
	Destroy();
}


ErrorStatus WindowImplCross::Create(const WindowDescription& description)
{
	m_Desc = description;

	xwin::WindowDesc windowDesc;
	windowDesc.name = m_Desc.nameId;
	windowDesc.title = m_Desc.title;
	windowDesc.iconPath = m_Desc.iconPath;
	windowDesc.width = m_Desc.width;
	windowDesc.height = m_Desc.height;
	windowDesc.resizable = m_Desc.resizable;
	windowDesc.minimizable = m_Desc.minimizable;
	windowDesc.visible = true;

	const bool created = m_XHandle.create(windowDesc, m_XEventQueue);
	if (not created)
	{
		return ErrorStatus::CREATE_FAILED;
	}

	m_Events.reserve(10);

	TTRACE("Created, id: {} title: {} iconPath: {}", m_Desc.nameId, m_Desc.title, m_Desc.iconPath);
	return ErrorStatus::OK;
}


void WindowImplCross::Destroy()
{
	Close();
	TTRACE("Destroyed");
}


void WindowImplCross::Close()
{
	m_XHandle.close();
	TTRACE("Closed");
}


void WindowImplCross::Update()
{
	m_XEventQueue.update();

	while (not m_XEventQueue.empty())
	{
		const xwin::Event& xEvent = m_XEventQueue.front();

		if (xEvent.type == xwin::EventType::Resize)
		{
			ResizeWindowEventData resizeData{
				.width = xEvent.data.resize.width,
				.height = xEvent.data.resize.height
			};
			WindowEvent& addedEvent = m_Events.emplace_back();
			addedEvent.m_EventData.resizeData = resizeData;
			addedEvent.m_Type = WindowEventType::RESIZE;
		}

		if (xEvent.type == xwin::EventType::Close)
		{
			WindowEvent& addedEvent = m_Events.emplace_back();
			addedEvent.m_Type = WindowEventType::CLOSE;
		}

		m_XEventQueue.pop();
	}
}


bool WindowImplCross::HasPendingEvents() const
{
	return not m_Events.empty();
}


WindowEvent WindowImplCross::GetNextEvent()
{
	WindowEvent event = m_Events.back();
	m_Events.pop_back();
	return event;
}

}
