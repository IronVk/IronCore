//
// Created by adnan on 6/30/25.
//
#pragma once
#ifndef VULKCOMMON_H
#define VULKCOMMON_H
#include <vulkan/vulkan.h>
#include <vector>

#include "../external/glfw/WindowManager.h"

typedef struct {
    int graphicsFamilyIndex;
    int presentationFamilyIndex;
    bool isValidGraphicsFamily() const {
        return graphicsFamilyIndex >=0;
    }
    bool isValidPresentationFamily() const {
        return presentationFamilyIndex >=0;
    }
} QueueFamilyIndices;

// type to hold device related infos
typedef  struct {
    VkPhysicalDevice physicalDevice;
    VkDevice logicalDevice;
    VkPhysicalDeviceFeatures deviceFeatures;
} MainDevice;

typedef struct {
    VkQueue graphicsQueue;
    VkQueue presentationQueue;
} QueueList;


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
}SwapChainImage;

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
    std::vector<const char*> extensions;
    std::vector<const char*> validationLayers;
} ExtensionAdapter;



#endif //VULKCOMMON_H
