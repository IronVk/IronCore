//
// Created by adnan on 6/30/25.
//

#include "VulkDevice.h"
#include <iostream>
#include <optional>
#include <vector>
#include "../Util/diagnostic/InstanceInitializationError.h"
#include "../Util/diagnostic/VULK_Diagnostic.h"
#include <vulkan/vulkan.h>

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
VkPhysicalDeviceFeatures getPhysicalDeviceFeatures(const VkPhysicalDevice &physicalDevice) {
    // Get the features supported by the GPU
    VkPhysicalDeviceFeatures supportedFeatures;
    vkGetPhysicalDeviceFeatures(physicalDevice, &supportedFeatures);
    return supportedFeatures;
}

VkPhysicalDevice pickSuitablePhysicalDevice(const std::vector<VkPhysicalDevice> &physical_devices) {
    if (physical_devices.empty())throw std::logic_error(VULK_LOGIC_ERROR("Can\'t pick from Empty Physical Device List"));
    for (const auto device:physical_devices ) {
        auto featureSet = getPhysicalDeviceFeatures(device);
        auto properties = getPhysicalDeviceProperties(device);
        if (featureSet.geometryShader && properties.deviceType==VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
            std::cout<<"selecting: "<<properties.deviceName<<" ["<<properties.deviceID<<"] "<<std::endl;
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



// Logical Device Helpers
VkDeviceQueueCreateInfo createDeviceQueueInfo(QueueFamilyIndices indices) {
    if (!indices.isValidGraphicsFamily())throw InstanceInitializationError(VULK_INSTANCE_INITIALIZATION_ERROR("Could not initialize device queue create info"));
    const float queuePriority = 1.0f;
    VkDeviceQueueCreateInfo deviceQueueCreateInfo = {};
    deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    deviceQueueCreateInfo.queueCount = 1;
    deviceQueueCreateInfo.queueFamilyIndex = indices.graphicsFamilyIndex;
    deviceQueueCreateInfo.pQueuePriorities = &queuePriority;
    return deviceQueueCreateInfo;
}

VkDeviceCreateInfo createLogicalDeviceInfo(const VkDeviceQueueCreateInfo& queueCreateInfo, const MainDevice& device, bool useValidation, std::vector<const char *> &validationLayers) {
    VkDeviceCreateInfo deviceCreateInfo = {};
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.queueCreateInfoCount = 1;
    deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
    deviceCreateInfo.enabledExtensionCount = 0; // we dont need it for device
    deviceCreateInfo.ppEnabledExtensionNames = nullptr; // we're not using any extensions for our logical device
    deviceCreateInfo.pEnabledFeatures = &device.deviceFeatures;
    if (useValidation && !validationLayers.empty()) {
        deviceCreateInfo.enabledLayerCount = validationLayers.size();
        deviceCreateInfo.ppEnabledLayerNames = validationLayers.data();
    }
    return deviceCreateInfo;

}




