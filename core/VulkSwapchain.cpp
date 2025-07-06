//
// Created by adnan on 6/30/25.
//

#include "VulkSwapchain.h"

bool createSurface(VkInstance instance, GLFWwindow& window, VkSurfaceKHR& surface) {
    if (glfwCreateWindowSurface(instance,&window,nullptr,&surface)!=VK_SUCCESS) {
        throw std::runtime_error(VULK_RUNTIME_ERROR("Window Surface Creation Error"));
    }
    return true;
}

SwapChainInfo getSwapChainInfo(const VkPhysicalDevice& physical_device,const DisplayAdapter& display_adapter) {
    SwapChainInfo swapChainInfo = {};
    //parsing surface capabilities from device
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physical_device,display_adapter.surface,&swapChainInfo.surfaceCapabilities);
    // parsing format from device
    uint32_t formatCount = 0;
    vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device,display_adapter.surface,&formatCount,nullptr);
    swapChainInfo.surfaceFormats.resize(formatCount);
    if (formatCount<1) throw std::runtime_error(VULK_RUNTIME_ERROR("Cound not detect surface format"));
    vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device,display_adapter.surface,&formatCount,swapChainInfo.surfaceFormats.data());
    //parsing presentation modes from device
    uint32_t presentationModeCount = 0;
    vkGetPhysicalDeviceSurfacePresentModesKHR(physical_device,display_adapter.surface,&presentationModeCount,nullptr);
    if (presentationModeCount<1) throw std::runtime_error(VULK_RUNTIME_ERROR("Cound not detect presentation modes"));
    swapChainInfo.presentModes.resize(presentationModeCount);
    vkGetPhysicalDeviceSurfacePresentModesKHR(physical_device,display_adapter.surface,&presentationModeCount,swapChainInfo.presentModes.data());
    return swapChainInfo;
}