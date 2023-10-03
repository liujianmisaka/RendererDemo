cmake_minimum_required(VERSION 3.20.0)
project(RendererDemo VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(RendererDemo main.cpp Application.h Application.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
