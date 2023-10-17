#include <string>
#include "Misaka/Core/Application.hpp"

namespace RendererDemo {

class DemoApplication : public Application {
public:
    virtual ~DemoApplication() override = default;

    virtual std::string GetAppName() override { return m_AppName; }

private:
    std::string m_AppName = "DemoApplication";
};

Application* CreateApplicationInstace() { return new DemoApplication(); }

} // namespace RendererDemo
