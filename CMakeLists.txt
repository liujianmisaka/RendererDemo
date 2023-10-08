cmake_minimum_required(VERSION 3.20.0)
project(RendererDemo VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

include(CTest)
enable_testing()

find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

set(
RendererDemo_SRC 
    main.cpp 
    Application.hpp Application.cpp
    Window.hpp Window.cpp
    Renderer.hpp Renderer.cpp
    Log.hpp Log.cpp
)

add_executable(RendererDemo ${RendererDemo_SRC})
target_link_libraries(
RendererDemo
PRIVATE
    glfw
    glm::glm
    spdlog::spdlog
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)