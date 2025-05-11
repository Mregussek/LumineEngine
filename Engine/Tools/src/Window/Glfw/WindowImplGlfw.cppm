
module;

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <memory>
#include <vector>

export module WindowImplGlfw;

import IWindow;
import WindowEvent;


export namespace lumine
{

class WindowImplGlfw : public IWindow
{

	struct GLFWwindowDeleter
	{
		void operator()(GLFWwindow* pPointer)
		{
			glfwDestroyWindow(pPointer);
		}
	};

public:

	~WindowImplGlfw();

public:

	ErrorStatus Create(const WindowDescription& description) override;
	void Destroy() override;

	void Update() override;
	void Close() override;

	[[nodiscard]] bool HasPendingEvents() const override;
	[[nodiscard]] WindowEvent GetNextEvent() override;

	[[nodiscard]] WindowRawHandle GetRawHandle() const override;

private:

	WindowDescription m_Desc{};
	std::unique_ptr<GLFWwindow, GLFWwindowDeleter> m_pWindow{};
	std::vector<WindowEvent> m_Events{};
	bool m_Created{ false };

};

}
