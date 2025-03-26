
module;

import Window;
#include <memory>

export module WindowSurface;


export namespace lumine::graphics
{

class WindowSurface
{
public:


private:

	std::shared_ptr<Window> m_pWindowHandle{ nullptr };

};

}
