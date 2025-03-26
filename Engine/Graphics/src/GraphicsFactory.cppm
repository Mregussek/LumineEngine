
module;

#include <memory>

export module GraphicsFactory;


export namespace lumine::graphics
{

class GraphicsFactory {
public:

    virtual ~GraphicsFactory();

public:

    virtual void Initialize();
    virtual void Close();

private:

    std::unique_ptr<GraphicsFactory> m_pConcreteFactory{};
    bool m_Initialized{ false };

};

}
