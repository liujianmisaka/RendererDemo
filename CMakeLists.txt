cmake_minimum_required(VERSION 3.20.0)
project(RendererDemo VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

include(CTest)
enable_testing()

find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_executable(RendererDemo main.cpp Application.h Application.cpp)
target_link_libraries(RendererDemo PRIVATE glfw)
target_link_libraries(RendererDemo PRIVATE glm::glm)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)