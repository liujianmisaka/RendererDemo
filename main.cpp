#include <iostream>
#include "Application.h"


int main() {
    RendererDemo::Application app;

    std::cout << "RendererDemo Running!\n";

    app.run();

    std::cout << "RendererDemo Closed!\n";
}