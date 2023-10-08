cmake_minimum_required(VERSION 3.20.0)
project(RendererDemo VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

include(CTest)
enable_testing()

find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

set(
RendererDemo_SRC 
    main.cpp 
    Application.hpp Application.cpp
    Window.hpp Window.cpp
)

add_executable(RendererDemo ${RendererDemo_SRC})
target_link_libraries(RendererDemo PRIVATE glfw)
target_link_libraries(RendererDemo PRIVATE glm::glm)

target_include_directories(RendererDemo PRIVATE glfw)
target_include_directories(RendererDemo PRIVATE glm::glm)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)