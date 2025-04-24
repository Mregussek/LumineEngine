
module;

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <memory>
#include <vector>

export module WindowImplGlfw;

import Window;
import WindowEvent;


export namespace lumine
{

class WindowImplGlfw : public Window
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

	bool HasPendingEvents() const override;
	WindowEvent GetNextEvent() override;

private:

	WindowDescription m_Desc{};
	std::unique_ptr<GLFWwindow, GLFWwindowDeleter> m_pWindow{};
	std::vector<WindowEvent> m_Events{};
	bool m_Created{ false };

};

}
