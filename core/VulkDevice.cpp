//
// Created by adnan on 6/30/25.
//

#include "VulkDevice.h"
#include <iostream>
#include <cstring>
#include <vector>
#include "../Util/diagnostic/InstanceInitializationError.h"
#include "../Util/diagnostic/VULK_Diagnostic.h"
#include <vulkan/vulkan.h>

std::vector<VkPhysicalDevice> getPhysicalDeviceList(VkInstance &instance) {
    u32 physicalDeviceCount = 0;
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

VkPhysicalDevice pickSuitablePhysicalDevice(const std::vector<VkPhysicalDevice> &physical_devices,std::vector<const char*>& given_extensions) {
    if (physical_devices.empty())throw std::logic_error(VULK_LOGIC_ERROR("Can\'t pick from Empty Physical Device List"));
    int devices_list_len = physical_devices.size();
    for (auto i=0; i < devices_list_len; i++ ) {
        VkPhysicalDevice device = physical_devices[i];
        auto featureSet = getPhysicalDeviceFeatures(device);
        auto properties = getPhysicalDeviceProperties(device);
        if (featureSet.geometryShader && (properties.deviceType==VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU || properties.deviceType==VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU) && checkPhysicalDeviceExtensionSupport(device,given_extensions)) {
            VLOG("Selecting ${}\n",properties.deviceName);
            return device;
        }
    }
    VLOG("SUitable Device Detection Failed.Feature Missing.Fallback to Default Device")
    return physical_devices[0];
}

bool checkPhysicalDeviceExtensionSupport(VkPhysicalDevice &device, std::vector<const char *> &given_extensions) {
    u32 ext_count = 0;
    vkEnumerateDeviceExtensionProperties(device,nullptr,&ext_count,nullptr);
    if (ext_count<0)return false;
    std::vector<VkExtensionProperties> extensionHolder = std::vector<VkExtensionProperties>(ext_count);
    vkEnumerateDeviceExtensionProperties(device,nullptr,&ext_count,extensionHolder.data());
    //std::cout<<"extension count: "<<given_extensions.size()<<std::endl;
    for (const auto &ext:given_extensions) {
        auto found = false;
        for (const auto &available_ext:extensionHolder) {
            //std::cout<<"current given extension: "<<ext<<"\t checking with available: "<<available_ext.extensionName<<std::endl;
            if (strcmp(available_ext.extensionName,ext)==0) {
                found=true;
                break;
            }
        }
        if (!found) {
            return false;
        };
    }
    return true;
}

std::vector<VkQueueFamilyProperties> getQueueFamilies(const VkPhysicalDevice& physical_device) {
    u32 queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physical_device,&queueFamilyCount,nullptr);
    auto queueFamilyList = std::vector<VkQueueFamilyProperties>(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(physical_device,&queueFamilyCount,queueFamilyList.data());
    if (queueFamilyList.empty())throw std::runtime_error(VULK_RUNTIME_ERROR("No QUEUE FAMILIES FOUND"));
    return queueFamilyList;
}

QueueFamilyIndices getGraphicsQueueFamilyIndices(const std::vector<VkQueueFamilyProperties>& queueFamilyList) {
    QueueFamilyIndices Indices;
    for (u8 i=0;i<queueFamilyList.size();i++) {
        const auto queueFamily = queueFamilyList[i];
        //? checking if queue family has at least one queue then checking if  first byte of queueFlags binary is 1 using bit manipulation
        if (queueFamily.queueCount> 0  && (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)) {
            Indices.graphicsFamilyIndex = i;
            if (Indices.isValidGraphicsFamily()) break;

        }
    }
    return Indices;
}
bool doesQueueFamilySupportPresentation(const VkPhysicalDevice &physical_device, VkSurfaceKHR &surface, int index) {
    VkBool32 does_support_presentation = VK_FALSE;
    vkGetPhysicalDeviceSurfaceSupportKHR(physical_device,index,surface,&does_support_presentation);
    return does_support_presentation==VK_TRUE;
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

VkDeviceCreateInfo createLogicalDeviceInfo(const VkDeviceQueueCreateInfo& queueCreateInfo, const MainDevice& device, bool useValidation,ExtensionAdapter &extensionAdapter) {
    VkDeviceCreateInfo deviceCreateInfo = {};
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.queueCreateInfoCount = 1;
    deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
    deviceCreateInfo.enabledExtensionCount = static_cast<u32>(extensionAdapter.extensions.size()); // we dont need it for device
    deviceCreateInfo.ppEnabledExtensionNames = extensionAdapter.extensions.data(); // we're not using any extensions for our logical device
    deviceCreateInfo.pEnabledFeatures = &device.deviceFeatures;
    if (useValidation && !extensionAdapter.validationLayers.empty()) {
        deviceCreateInfo.enabledLayerCount = extensionAdapter.validationLayers.size();
        deviceCreateInfo.ppEnabledLayerNames = extensionAdapter.validationLayers.data();
    }
    return deviceCreateInfo;

}




