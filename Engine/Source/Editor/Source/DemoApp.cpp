#include <string>
#include "Runtime/Core/Application.hpp"

namespace RendererDemo {

class DemoApplication : public Application {
public:
    virtual ~DemoApplication() override = default;

    virtual const std::string& GetClassName() override { return m_AppName; }

private:
    std::string m_AppName = "DemoApplication";
};

Application* CreateApplicationInstace() { return new DemoApplication(); }

} // namespace RendererDemo
