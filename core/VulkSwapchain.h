//
// Created by adnan on 6/30/25.
//
#pragma once
#ifndef VULKSWAPCHAIN_H
#define VULKSWAPCHAIN_H
#include "VulkInfoInstance.h"


bool createSurface(VkInstance instance, GLFWwindow& window, VkSurfaceKHR& surface) ;

SwapChainInfo getSwapChainInfo(const VkPhysicalDevice& physical_device,const DisplayAdapter& display_adapter);

VkSurfaceFormatKHR pickSuitableSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &formats);
VkPresentModeKHR pickSuitablePresentMode(const std::vector<VkPresentModeKHR> &presentationModes);
VkExtent2D pickSuitableExtent(const VkSurfaceCapabilitiesKHR &capabilities);
bool createSwapChain(AppContext& context,DisplayAdapter& displayAdapter);
std::vector<VkImage> getSwapChainImages(AppContext& context,DisplayAdapter& displayAdapter);
VkImageView createImageView(AppContext& context,DisplayAdapter& displayAdapter,VkImage& img);
#endif //VULKSWAPCHAIN_H
