
module;

import Window;
#include <memory>

export module ToolsFactory;


export namespace lumine
{

class ToolsFactory {
public:

    virtual ~ToolsFactory();

public:

    void Initialize();
    void Close();

public:

    std::shared_ptr<Window> GetWindow() const;

};

}
