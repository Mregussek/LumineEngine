
module;

#include <memory>

export module ToolsFactory;

import Window;


export namespace lumine
{

class ToolsFactory {
public:

    virtual ~ToolsFactory();

public:

    void Initialize();
    void Close();

public:

    std::shared_ptr<Window> CreateWindow() const;

};

}
