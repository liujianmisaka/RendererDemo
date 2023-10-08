#include <iostream>
#include "Application.hpp"


int main() {
    RendererDemo::ApplicationInfo appInfo {};
    RendererDemo::Application app {appInfo};

    std::cout << "RendererDemo Running!\n";

    app.run();

    std::cout << "RendererDemo Closed!\n";
}