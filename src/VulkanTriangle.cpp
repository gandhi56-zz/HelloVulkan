//
// Created by anshil on 2021-02-01.
//

#include "../include/VulkanTriangle.h"


void VulkanTriangle::initWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
}

void VulkanTriangle::initVulkan(){
    createInstance();
}

void VulkanTriangle::mainLoop(){
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}

void VulkanTriangle::cleanup(){
    glfwDestroyWindow(window);
    glfwTerminate();
}

void VulkanTriangle::createInstance() {
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;
}
