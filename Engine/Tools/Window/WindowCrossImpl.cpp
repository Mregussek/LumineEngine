﻿
module;

#include "TLogger.h"
#include "CrossWindow/CrossWindow.h"
import WindowEvent;

module WindowCrossImpl;


namespace lumine
{

WindowCrossImpl::~WindowCrossImpl()
{
	Destroy();
}


ErrorStatus WindowCrossImpl::Create(const WindowDescription& description)
{
	xwin::WindowDesc windowDesc;
	windowDesc.name = std::string{ description.nameId };
	windowDesc.title = std::string{ description.title };
	windowDesc.visible = true;
	windowDesc.width = description.width;
	windowDesc.height = description.height;

	const bool created = m_XHandle.create(windowDesc, m_XEventQueue);
	if (not created)
	{
		return ErrorStatus::CREATE_FAILED;
	}

	m_Events.reserve(10);

	TTRACE("Created");
	return ErrorStatus::OK;
}


void WindowCrossImpl::Destroy()
{
	Close();
	TTRACE("Destroyed");
}


void WindowCrossImpl::Close()
{
	m_XHandle.close();
	TTRACE("Closed");
}


void WindowCrossImpl::Update()
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


bool WindowCrossImpl::HasPendingEvents() const
{
	return not m_Events.empty();
}


WindowEvent WindowCrossImpl::GetNextEvent()
{
	WindowEvent event = m_Events.back();
	m_Events.pop_back();
	return event;
}

}
