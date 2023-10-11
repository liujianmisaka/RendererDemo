#include "Misaka/Application.hpp"

#include "Misaka/Log.hpp"


int main() {
    RendererDemo::Log::Init();

    RendererDemo::Application app {};

    LOGGER_CORE_WARN("RendererDemo Running!");

    app.run();

    LOGGER_CORE_WARN("RendererDemo Closed!");
}