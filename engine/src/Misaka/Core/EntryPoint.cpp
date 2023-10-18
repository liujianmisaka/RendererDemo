#include "Misaka/Core/Application.hpp"

#include "Misaka/Utils/Log.hpp"

extern RendererDemo::Application* RendererDemo::CreateApplicationInstace();

int main() {
    RendererDemo::Log::Init();

    RendererDemo::Application* app = RendererDemo::CreateApplicationInstace();

    LOGGER_CORE_WARN("RendererDemo Running!");
	
    LOGGER_CORE_INFO(app->GetClassName().c_str());
	app->Initialize();
    app->Run();
	app->Destroy();

    delete app;

    LOGGER_CORE_WARN("RendererDemo Closed!");
}
