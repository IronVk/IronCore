//
// Created by adnan on 6/30/25.
//

#ifndef VULKSWAPCHAIN_H
#define VULKSWAPCHAIN_H
#include "VulkInfoInstance.h"


bool createSurface(VkInstance instance, GLFWwindow& window, VkSurfaceKHR& surface) ;

SwapChainInfo getSwapChainInfo(const VkPhysicalDevice& physical_device,const DisplayAdapter& display_adapter);


#endif //VULKSWAPCHAIN_H
