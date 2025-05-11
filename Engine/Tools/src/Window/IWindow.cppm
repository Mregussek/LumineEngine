
module;

#include "Types.h"
#include <string>

export module IWindow;

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


class IWindow {
public:

	virtual ~IWindow() = default;

public:

	virtual ErrorStatus Create(const WindowDescription& description) = 0;
	virtual void Destroy() = 0;

	virtual void Update() = 0;
	virtual void Close() = 0;

	virtual bool HasPendingEvents() const = 0;
	virtual WindowEvent GetNextEvent() = 0;

};

}
