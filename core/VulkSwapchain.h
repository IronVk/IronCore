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
bool createSwapChain(const AppContext& context,DisplayAdapter& displayAdapter);
std::vector<VkImage> getSwapChainImages(const AppContext& context, const DisplayAdapter& displayAdapter);
VkImageView createImageView(const AppContext& context,const VkImage& img);
#endif //VULKSWAPCHAIN_H
