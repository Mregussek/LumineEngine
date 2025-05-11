
module;

#include <memory>

export module ToolsFactory;

import IWindow;


export namespace lumine
{

class ToolsFactory {
public:

    virtual ~ToolsFactory();

public:

    void Initialize();
    void Close();

public:

    std::shared_ptr<IWindow> CreateWindow() const;

};

}
