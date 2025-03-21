
module;

import Window;
import WindowEvent;
#include "CrossWindow/CrossWindow.h"
#include <vector>

export module WindowImplCross;


export namespace lumine
{

class WindowImplCross : public Window {
public:

	~WindowImplCross();

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
	WindowDescription m_Desc{};
	bool m_PendingEvents{ false };

};

}
