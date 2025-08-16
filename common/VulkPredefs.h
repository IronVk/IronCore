//
// Created by adnan on 6/30/25.
//
//# VULK
#pragma once
#ifndef VULKCOMMON_H
#define VULKCOMMON_H
#include <vulkan/vulkan.h>
#include <vector>
#include "../external/glfw/WindowManager.h"
#include "NumericDefs.h"

//*Forward declaring Graphics Pipeline
class GraphicsPipeline;

//@ 🚩 flag to check mode of the app
inline thread_local bool prod_mode;

typedef struct {
    int graphicsFamilyIndex;
    int presentationFamilyIndex;

    bool isValidGraphicsFamily() const {
        return graphicsFamilyIndex >= ZERO;
    }

    bool isValidPresentationFamily() const {
        return presentationFamilyIndex >= ZERO;
    }
} QueueFamilyIndices;



// type to hold device related infos
typedef struct {
    VkPhysicalDevice physicalDevice;
    VkDevice logicalDevice;
    VkPhysicalDeviceFeatures deviceFeatures;
} MainDevice;

typedef struct{
    VkQueue graphicsQueue;
    VkQueue presentationQueue;
} QueueList;

//* AppContext holds everything required for application Context
typedef struct {
    VkInstance Instance;
    MainDevice Device;
    VkDebugUtilsMessengerEXT debugMessenger;
    QueueFamilyIndices queueFamilyIndices;
} AppContext;


typedef struct {
    VkSurfaceCapabilitiesKHR surfaceCapabilities;
    std::vector<VkSurfaceFormatKHR> surfaceFormats;
    std::vector<VkPresentModeKHR> presentModes;
} SwapChainInfo;

typedef struct {
    VkImage image;
    VkImageView imageView;
} SwapChainImage;

typedef struct {
    GLFWwindow *Window;
    VkSurfaceKHR surface;
    VkSwapchainKHR swapchain;
    SwapChainInfo swapChainInfo;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<SwapChainImage> swapChainImages;
} DisplayAdapter;

typedef struct {
    std::vector<const char *> extensions;
    std::vector<const char *> validationLayers;
} ExtensionAdapter;

typedef enum {
    RGBA = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,
    RGB = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT,
    RG = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT,
    R = VK_COLOR_COMPONENT_R_BIT,
    G = VK_COLOR_COMPONENT_G_BIT,
    B = VK_COLOR_COMPONENT_B_BIT,
    A = VK_COLOR_COMPONENT_A_BIT
} COLOR_WRITE_MASK;



typedef struct {
    AppContext& pApplicationContext;
    QueueFamilyIndices& pQueueFamilyIndices;
    DisplayAdapter& pDisplayAdapter;
    GraphicsPipeline& pGraphicsPipeline;
    QueueList& pQueueList;
}RenderInitInfo;

#endif //VULKCOMMON_H



