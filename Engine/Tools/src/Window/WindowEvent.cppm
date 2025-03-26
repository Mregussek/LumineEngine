
module;

#include "Types.h"

export module WindowEvent;


export namespace lumine
{

enum class WindowEventType
{
	NONE, RESIZE, CLOSE
};


struct ResizeWindowEventData
{
	u32 width{ 0 };
	u32 height{ 0 };
};


struct EventData
{
	ResizeWindowEventData resizeData;
};


class WindowEvent
{
	friend class WindowImplCross;
	friend class WindowImplGlfw;

public:

	bool IsResize() const;
	ResizeWindowEventData GetResizeData() const;

	bool IsClose() const;

private:

	EventData m_EventData;
	WindowEventType m_Type{ WindowEventType::NONE };

};

}
