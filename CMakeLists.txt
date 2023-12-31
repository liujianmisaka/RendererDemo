cmake_minimum_required(VERSION 3.20.0)
project(RendererDemo VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

include(CTest)
enable_testing()

find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)
find_package(VulkanHeaders CONFIG)
find_package(assimp CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)

file(
GLOB_RECURSE RendererDemo_SRC 
	Engine/Source/*
)
list(FILTER RendererDemo_SRC EXCLUDE REGEX "Engine/Source/Test/*")

add_executable(RendererDemo ${RendererDemo_SRC})
target_link_libraries(
RendererDemo
PRIVATE
    glfw
    glm::glm
    spdlog::spdlog
    glad::glad
    imgui::imgui
	EnTT::EnTT
	Vulkan::Headers
	assimp::assimp
	yaml-cpp::yaml-cpp
)

target_include_directories(RendererDemo PRIVATE Engine/Source)

add_executable(ImGuiTest Engine/Source/Test/ImGuiTest.cpp)
target_link_libraries(ImGuiTest PRIVATE glfw glad::glad imgui::imgui)
add_test(NAME ImGuiTest COMMAND ImGuiTest)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
