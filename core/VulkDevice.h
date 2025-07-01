//
// Created by adnan on 6/30/25.
//
#pragma once
#ifndef VULKDEVICE_H
#define VULKDEVICE_H
#include <vector>
#include <vulkan/vulkan.h>

#include "../common/VulkCommon.h"
//Device Related Functionalities
//? 1. Physical Device
std::vector<VkPhysicalDevice> getDeviceList(VkInstance& instance);

VkPhysicalDeviceProperties getPhysicalDeviceProperties(const VkPhysicalDevice &physical_device);

VkPhysicalDeviceFeatures getPhysicalDeviceFeatures(const VkPhysicalDevice &physical_device);

VkPhysicalDevice pickSuitablePhysicalDevice(const std::vector<VkPhysicalDevice>& physical_devices);

//* Queue Related Functionalities
std::vector<VkQueueFamilyProperties> getQueueFamilies(const VkPhysicalDevice &physical_device);

QueueFamilyIndices getGraphicsQueueFamilyIndices(const std::vector<VkQueueFamilyProperties>& queueFamilyList);


//? 2. Logical Device






#endif //VULKDEVICE_H
