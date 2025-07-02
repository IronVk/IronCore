//
// Created by adnan on 6/30/25.
//

#include "VulkDevice.h"
#include <iostream>
#include <vector>
#include <vulkan/vulkan.h>
#include "../Util/diagnostic/VULK_Diagnostic.h"

std::vector<VkPhysicalDevice> getPhysicalDeviceList(VkInstance &instance) {
    uint32_t physicalDeviceCount = 0;
    if (vkEnumeratePhysicalDevices(instance,&physicalDeviceCount,nullptr )!=VK_SUCCESS || physicalDeviceCount<1)throw std::runtime_error(VULK_RUNTIME_ERROR("No Device Found"));// ! if no device found
    auto physicalDevices = std::vector<VkPhysicalDevice>(physicalDeviceCount);
    vkEnumeratePhysicalDevices(instance,&physicalDeviceCount,physicalDevices.data());
    return physicalDevices;
}

VkPhysicalDeviceProperties getPhysicalDeviceProperties(const VkPhysicalDevice &physical_device) {
    VkPhysicalDeviceProperties properties;
    vkGetPhysicalDeviceProperties(physical_device,&properties);
    return properties;
}
VkPhysicalDeviceFeatures getPhysicalDeviceFeatures(const VkPhysicalDevice &physical_device) {
    VkPhysicalDeviceFeatures features;
    vkGetPhysicalDeviceFeatures(physical_device,&features);
    return features;
}

VkPhysicalDevice pickSuitablePhysicalDevice(const std::vector<VkPhysicalDevice> &physical_devices) {
    if (physical_devices.empty())throw std::logic_error(VULK_LOGIC_ERROR("Can\'t pick from Empty Physical Device List"));
    for (const auto device:physical_devices ) {
        auto featureSet = getPhysicalDeviceFeatures(device);
        auto properties = getPhysicalDeviceProperties(device);
        if (featureSet.geometryShader && properties.deviceType==VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
            return device;
        }
    }
    return physical_devices[0];
}

std::vector<VkQueueFamilyProperties> getQueueFamilies(const VkPhysicalDevice& physical_device) {
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physical_device,&queueFamilyCount,nullptr);
    auto queueFamilyList = std::vector<VkQueueFamilyProperties>(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(physical_device,&queueFamilyCount,queueFamilyList.data());
    if (queueFamilyList.empty())throw std::runtime_error(VULK_RUNTIME_ERROR("No QUEUE FAMILIES FOUND"));
    return queueFamilyList;
}

QueueFamilyIndices getGraphicsQueueFamilyIndices(const std::vector<VkQueueFamilyProperties>& queueFamilyList) {
    QueueFamilyIndices Indices;
    for (uint8_t i=0;i<queueFamilyList.size();i++) {
        const auto queueFamily = queueFamilyList[i];
        //? checking if queue family has at least one queue then checking if  first byte of queueFlags binary is 1 using bit manipulation
        if (queueFamily.queueCount> 0  && (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)) {
            Indices.graphicsFamilyIndex = i;
            if (Indices.isValidGraphicsFamily()) break;

        }
    }
    return Indices;
}

