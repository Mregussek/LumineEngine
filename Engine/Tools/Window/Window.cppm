
module;

#include "Types.h"
import WindowEvent;

export module Window;


export namespace lumine
{

struct WindowDescription
{
	u32 width{ 1600 };
	u32 height{ 900 };

	const char* nameId{ "" };
	const char* title{ "" };
	const char* iconPath{ "" };

	bool resizable{ false };
	bool minimizable{ false };
};


class Window {
public:

	virtual ~Window() {}

public:

	virtual ErrorStatus Create(const WindowDescription& description) { return ErrorStatus::CREATE_FAILED; }
	virtual void Destroy() {}

	virtual void Update() {}
	virtual void Close() {}

	virtual bool HasPendingEvents() const { return false; }
	virtual WindowEvent GetNextEvent() { return {}; }

};

}
