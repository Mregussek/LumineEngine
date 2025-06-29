
module;

#include "CrossWindow/CrossWindow.h"
#include <vector>

export module WindowImplCross;

import IWindow;
import WindowEvent;


export namespace lumine
{

class WindowImplCross : public IWindow {
public:

	~WindowImplCross();

public:

	ErrorStatus Create(const WindowDescription& description) override;
	void Destroy() override;

	void Update() override;
	void Close() override;

	[[nodiscard]] bool HasPendingEvents() const override;
	[[nodiscard]] WindowEvent GetNextEvent() override;

	[[nodiscard]] WindowRawHandle GetRawHandle() const override;

private:

	xwin::Window m_XHandle{};
	xwin::EventQueue m_XEventQueue{};
	std::vector<WindowEvent> m_Events{};
	WindowDescription m_Desc{};
	bool m_PendingEvents{ false };

};

}
