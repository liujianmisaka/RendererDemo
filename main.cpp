#include <iostream>
#include "Application.hpp"
#include "Log.hpp"


int main() {
    RendererDemo::Log::Init();

    RendererDemo::ApplicationInfo appInfo {};
    RendererDemo::Application app {appInfo};

    std::cout << "RendererDemo Running!\n";

    app.run();

    std::cout << "RendererDemo Closed!\n";
}