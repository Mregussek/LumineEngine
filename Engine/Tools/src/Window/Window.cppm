
module;

#include "Types.h"
#include <string>

export module Window;

import WindowEvent;


export namespace lumine
{

struct WindowDescription
{
	u32 width{ 1600 };
	u32 height{ 900 };

	std::string nameId{ "" };
	std::string title{ "" };
	std::string iconPath{ "" };

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
