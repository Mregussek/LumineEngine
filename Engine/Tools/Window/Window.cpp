
module;

#include "TLogger.h"

module Window;


namespace lumine
{

Window::~Window()
{
	Close();
}

void Window::Initialize()
{
	TTRACE("Initialized");
}

void Window::Close()
{
	TTRACE("Closed");
}

}
