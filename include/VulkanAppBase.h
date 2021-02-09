//
// Created by anshil on 2021-02-01.
//

#ifndef HELLOVULKAN_VULKANAPPBASE_H
#define HELLOVULKAN_VULKANAPPBASE_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <set>
#include <stdexcept>
#include <vector>

//== Global constants =================//
const int MAX_FRAMES_IN_FLIGHT = 2;
const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;
const std::vector<const char *> validationLayers = {"VK_LAYER_KHRONOS_validation"};
const std::vector<const char *> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

/**
 * @brief create debug utils messenger extension
 * @param instance
 * @param pCreateInfo
 * @param pAllocator
 * @param pDebugMessenger
 * @return status of the creation
 */
VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
                                      const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                                      const VkAllocationCallbacks *pAllocator,
                                      VkDebugUtilsMessengerEXT *pDebugMessenger);


/**
 * @brief destroy debug utils messenger
 * @param instance
 * @param debugMessenger
 * @param pAllocator
 */
void DestroyDebugUtilsMessengerEXT(VkInstance instance,
                                   VkDebugUtilsMessengerEXT debugMessenger,
                                   const VkAllocationCallbacks *pAllocator);

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                    VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                    const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                                                    void *pUserData);


struct QueueFamilyIndices {
  std::optional<uint32_t> graphicsFamily;
  std::optional<uint32_t> presentFamily;
  [[nodiscard]] bool isComplete() const {
    return graphicsFamily.has_value() and presentFamily.has_value();
  }
};

struct SwapChainSupportDetails {
  VkSurfaceCapabilitiesKHR capabilities;
  std::vector<VkSurfaceFormatKHR> formats;
  std::vector<VkPresentModeKHR> presentModes;
};

class VulkanAppBase {
public:
  void run();

private:
  GLFWwindow *window{};
  VkInstance instance{};
  VkDebugUtilsMessengerEXT debugMessenger{};
  VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
  VkDevice device{};
  VkQueue graphicsQueue{};
  VkQueue presentQueue{};
  VkSurfaceKHR surface{};

  VkSwapchainKHR swapChain;
  std::vector<VkImage> swapChainImages;
  VkFormat swapChainImageFormat;
  VkExtent2D swapChainExtent;

  std::vector<VkImageView> swapChainImageViews;

  VkRenderPass renderPass;
  VkPipelineLayout pipelineLayout;
  VkPipeline graphicsPipeline;

  std::vector<VkFramebuffer> swapChainFramebuffers;
  VkCommandPool commandPool;
  std::vector<VkCommandBuffer> commandBuffers;

  std::vector<VkSemaphore> imageAvailableSemaphores;
  std::vector<VkSemaphore> renderFinishedSemaphores;
  std::vector<VkFence> inFlightFences;
  std::vector<VkFence> imagesInFlight;
  size_t currentFrame = 0;

  bool framebufferResized = false;

  /**
   * @brief initialize glfw window: set width, height, title and GLFW hints
   */
  void initWindow();


  void initVulkan();
  void mainLoop();

  /**
   * @brief destroy device, surface, vulkan instance, window and
   * terminate program
   */
  void cleanup();

  /**
   * @brief define Vulkan app info, create info, get extensions, enable validation layers and create instance
   */
  void createInstance();

  /**
   * @brief enable validation layers if running in debug mode,
   *  define createInfo to create DebugUtilsMessenger
   */
  void setupDebugMessenger();

  /**
   * @brief populate the fields of the passed in createInfo struct object
   * @param createInfo
   */
  void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);

  /**
   * @brief determine whether this machine supports validation layers
   * @return
   */
  bool checkValidationLayerSupport();

  /**
   * @return vector of required extensions
   */
  std::vector<const char *> getRequiredExtensions();

  /**
   * @brief enumerate and evaluate available physical devices against the
   *  requirements of this application
   */
  void pickPhysicalDevice();

  /**
   * @brief helper function to check whether a physical device is suitable for running this application or not.
   * @param device reference to the physical device for check
   * @return whether or not device is suitable
   */
  bool isDeviceSuitable(VkPhysicalDevice device);

  /**
   * @brief Given a physical device, this method finds queue families. For each queue
   *  family, its corresponding graphics family and present support are determined.
   * @param device
   * @return
   */
  QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

  /**
   * @brief Assuming that the physical device is already initialized,
   *  create a logical device,
   *  define createInfos for each unique queueFamily and the logical device,
   *  enable validation layers for the logical device and finally create it.
   */
  void createLogicalDevice();

  /**
   * @brief create GLFW window surface to render graphics
   */
  void createSurface();

  /**
   * @brief create a queue for images to be presented
   */
  void createSwapChain();

  /**
   * @brief select the swap surface format by specifying the color channel and type
   * @param availableFormats
   * @return
   */
  VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);

  /**
   * @brief select presentation mode for images
   * @param availablePresentModes
   * @return
   */
  VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

  /**
   * @brief select the resolution of the swap chain images and it's almost always
   *  exactly equal to the resolution of the window that we're drawing to in pixels
   * @param capabilities
   * @return
   */
  VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

  /**
   * @brief get surface capabilities, physical device surface format, available
   *  presentation modes and return them as a SwapChainSupportDetails object
   * @param dev
   * @return
   */
  SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice dev);

  /**
   * @brief check if the device supports extensions
   * @param device
   * @return
   */
  bool checkDeviceExtensionSupport(VkPhysicalDevice device);

  /**
   * @brief creates a basic image view for every image in the swap chain
   * so that we can use them as color targets
   */
  void createImageViews();

  /**
   * @brief compilation and linking of spir-v bytecode happens here.
   */
  void createGraphicsPipeline();
  VkShaderModule createShaderModule(const std::vector<char>& code);

  /**
   * @brief create render pass by plugging in attachment description for colors,
   *  their reference, subpass description, and render pass create info
   */
  void createRenderPass();

  /**
    * @brief create swap chain frame buffers
    */
  void createFramebuffers();

  /**
   * @brief create a command pool to manage the memory that is used to store the buffers
   *  and command buffers are allocated from them
   */
  void createCommandPool();

  /**
   * @brief allocate command buffers and recording drawing commands in them
   */
  void createCommandBuffers();

  /**
   * @brief acquire an image from the swap chain
   */
  void drawFrame();

  /**
   * @brief create the image available semaphores, render finished semaphores and fences
   *  for GPU-GPU and CPU-GPU synchronization
   */
  void createSyncObjects();

  /**
   * @brief recreate the swap chain for cases of window resizing or reloads
   */
  void recreateSwapChain();

  /**
   * @brief destroy frame buffers, free command buffers, graphics pipeline, pipeline layout,
   *  render pass, swap chain image views, and swap chain itself
   */
  void cleanupSwapChain();

  /**
   * @brief callback for framebuffer resize
   * @param window
   * @param width
   * @param height
   */
  static void framebufferResizeCallback(GLFWwindow* window, int width , int height);
};


#endif//HELLOVULKAN_VULKANAPPBASE_H
