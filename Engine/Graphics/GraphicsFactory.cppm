
module;

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

    bool m_Initialized{ false };

};

}
