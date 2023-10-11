cmake_minimum_required(VERSION 3.20.0)
project(RendererDemo VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

include(CTest)
enable_testing()

find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

file(GLOB_RECURSE RendererDemo_SRC engine/src/*)

add_executable(RendererDemo ${RendererDemo_SRC})
target_link_libraries(
RendererDemo
PRIVATE
    glfw
    glm::glm
    spdlog::spdlog
    glad::glad
)

target_include_directories(RendererDemo PRIVATE engine/src)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)