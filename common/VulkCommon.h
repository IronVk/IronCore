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
    bool isValidGraphicsFamily() const {
        return graphicsFamilyIndex >=0;
    }
} QueueFamilyIndices;

// type to hold device related infos
typedef  struct {
    VkPhysicalDevice physicalDevice;
    VkDevice logicalDevice;
    VkPhysicalDeviceFeatures deviceFeatures;
} MainDevice;




typedef struct {
    VkInstance Instance;
    MainDevice Device;
    VkDebugUtilsMessengerEXT debugMessenger;
    QueueFamilyIndices queueFamilyIndices;
} VkContext;

typedef struct {
    GLFWwindow *Window;
    VkSurfaceKHR surface;
    VkSwapchainKHR swapchain;
} DisplayAdapter;

typedef struct {
    std::vector<const char*> extensions;
    std::vector<const char*> validationLayers;
} ExtensionAdapter;



#endif //VULKCOMMON_H
