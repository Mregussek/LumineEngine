
module;

#include <memory>

export module GraphicsFactory;

import BackendFactory;


export namespace lumine::graphics
{

class GraphicsFactory {
public:

    ~GraphicsFactory();

public:

    void Initialize();
    void Close();

private:

    std::unique_ptr<IBackendFactory> m_pBackendFactory{ nullptr };
    bool m_Initialized{ false };

};

}
