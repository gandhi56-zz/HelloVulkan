cmake_minimum_required(VERSION 3.17)
project(HelloVulkan)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER clang++)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(Vulkan REQUIRED FATAL_ERROR)

include_directories(include)
add_executable(HelloVulkan src/main.cpp src/VulkanAppBase.cpp)

target_link_libraries(HelloVulkan glfw OpenGL::GL vulkan)