//
// Created by anshil on 2021-02-01.
//

#ifndef HELLOVULKAN_VULKANTRIANGLE_H
#define HELLOVULKAN_VULKANTRIANGLE_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <memory>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

struct DestroyGLFWwindow{
    void operator()(GLFWwindow* ptr){
        glfwDestroyWindow(ptr);
    }
};

class VulkanTriangle {
public:
    void run(){
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    GLFWwindow* window;
    VkInstance instance;

    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanup();
    void createInstance();
};


#endif //HELLOVULKAN_VULKANTRIANGLE_H
