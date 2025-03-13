
module;

import Tools;
#include <iostream>

module Graphics;

namespace graphics
{


void GraphicsClass::hello()
{
    std::cout << "Hello from Graphics\n";
}


void GraphicsClass::use_tools()
{
    tools::ToolsClass tools;
    tools.hello();
}


}
