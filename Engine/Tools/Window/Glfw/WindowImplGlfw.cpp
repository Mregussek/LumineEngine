
module;

#include "Types.h"
#include "TLogger.h"
import WindowEvent;
import Path;

#include <GLFW/glfw3.h>
#include <stb_image.h>

module WindowImplGlfw;


namespace lumine
{


static void ErrorCallback(int error, const char* description)
{
	TERROR("Error {}: {}", error, description);
}


class Icon
{
public:

	~Icon()
	{
		Free();
	}

	bool Load(const char* path)
	{
		if (not Path::Exists(Path{ path }))
		{
			TERROR("Not existing icon path: {}", path);
			return false;
		}

		int width{ 0 }, height{ 0 };
		m_pPixels = stbi_load(path, &width, &height, nullptr, 4);
		if (not m_pPixels) {
			TERROR("Failed to load window icon! path: {} width {} height {}", path, width, height);
			return false;
		}

		m_GlfwImage.width = width;
		m_GlfwImage.height = height;
		m_GlfwImage.pixels = m_pPixels;

		m_Loaded = true;
		TTRACE("Loaded window icon: {}", path);
	}

	GLFWimage* GetData() { return &m_GlfwImage; }

private:

	void Free()
	{
		if (m_Loaded)
		{
			stbi_image_free(m_pPixels);
			m_pPixels = nullptr;
			m_Loaded = false;
		}

		TTRACE("Window icon memory freed");
	}

	GLFWimage m_GlfwImage{};
	unsigned char* m_pPixels{ nullptr };
	bool m_Loaded{ false };

};


}


namespace lumine
{

WindowImplGlfw::~WindowImplGlfw()
{
	Destroy();
}


ErrorStatus WindowImplGlfw::Create(const WindowDescription& description)
{
	m_Desc = description;

	glfwSetErrorCallback(ErrorCallback);

	i32 initialized = glfwInit();
	if (not initialized)
	{
		const char* msg{ "Cannot initialize glfw!" };
		TCRITICAL(msg);
		return ErrorStatus::CREATE_FAILED;
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, m_Desc.resizable ? GLFW_TRUE : GLFW_FALSE);

	m_pWindow = std::unique_ptr<GLFWwindow, GLFWwindowDeleter>(
		glfwCreateWindow(m_Desc.width, m_Desc.height, m_Desc.title.c_str(), nullptr, nullptr)
	);

	Icon icon{};
	bool loaded = icon.Load(m_Desc.iconPath.c_str());
	if (loaded)
	{
		glfwSetWindowIcon(m_pWindow.get(), 1, icon.GetData());
	}
	
	// glfwSetCursorPosCallback(m_pWindow.get(), CursorPosCallback);
	// glfwSetMouseButtonCallback(m_pWindow.get(), MouseButtonCallback);
	// glfwSetKeyCallback(m_pWindow.get(), KeyboardButtonCallback);
	// glfwSetScrollCallback(m_pWindow.get(), ScrollCallback);
	// glfwSetInputMode(m_pWindow.get(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	m_Events.reserve(10);

	m_Created = true;
	TTRACE("Created, id: {} title: {} iconPath: {}", m_Desc.nameId, m_Desc.title, m_Desc.iconPath);
	return ErrorStatus::OK;
}


void WindowImplGlfw::Destroy()
{
	if (m_Created)
	{
		return;
	}

	Close();
	m_pWindow.reset();
	glfwTerminate();
	m_Created = false;
	TTRACE("Destroyed");
}


void WindowImplGlfw::Close()
{
	glfwSetWindowShouldClose(m_pWindow.get(), GLFW_TRUE);
	TTRACE("Closed");
}


void WindowImplGlfw::Update()
{
	glfwPollEvents();

	if (glfwWindowShouldClose(m_pWindow.get()))
	{
		WindowEvent& addedEvent = m_Events.emplace_back();
		addedEvent.m_Type = WindowEventType::CLOSE;
	}
}


bool WindowImplGlfw::HasPendingEvents() const
{
	return not m_Events.empty();
}


WindowEvent WindowImplGlfw::GetNextEvent()
{
	WindowEvent event = m_Events.back();
	m_Events.pop_back();
	return event;
}

}
