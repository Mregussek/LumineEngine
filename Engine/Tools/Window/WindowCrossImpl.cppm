
module;

import Window;
import WindowEvent;
#include "CrossWindow/CrossWindow.h"
#include <vector>

export module WindowCrossImpl;


export namespace lumine
{

class WindowCrossImpl : public Window {
public:

	~WindowCrossImpl();

public:

	ErrorStatus Create(const WindowDescription& description) override;
	void Destroy() override;

	void Update() override;
	void Close() override;

	bool HasPendingEvents() const override;
	WindowEvent GetNextEvent() override;

private:

	xwin::Window m_XHandle{};
	xwin::EventQueue m_XEventQueue{};
	std::vector<WindowEvent> m_Events{};
	bool m_PendingEvents{ false };

};

}
