//
// Created by adnan on 6/30/25.
//

#include "VulkContext.h"
#include <iostream>
#include "VulkDebug.h"
#include "VulkDevice.h"
#include "VulkInfoInstance.h"
#include "../Util/diagnostic/InstanceInitializationError.h"

VulkContext::VulkContext(VulkConf vulk_conf)  {
        this->useValidation = vulk_conf.build_mode == BuildMode::DEV;
        this->appName = vulk_conf.app_name;
        this->engineName = vulk_conf.engine_name;
        this->displayAdapter.Window = vulk_conf.window;
        this->displayAdapter.surface = VK_NULL_HANDLE;
        this->displayAdapter.swapchain = VK_NULL_HANDLE;
        this->context.Instance = VK_NULL_HANDLE;
        this->context.Device.physicalDevice = VK_NULL_HANDLE;
        this->context.Device.logicalDevice = VK_NULL_HANDLE;
        this->extensionAdapter.validationLayers = { "VK_LAYER_KHRONOS_validation"};
        this->extensionAdapter.extensions = vulk_conf.extensions;
}



VulkContext::~VulkContext() {
    this->dropContext();
}


void VulkContext::createContext() {
    if (this->appName.empty() || this->engineName.empty() || this->extensionAdapter.extensions.empty()) InstanceInitializationError(VULK_INSTANCE_INITIALIZATION_ERROR("Required Info Missing to create Vulk Context"));
    auto appInfo = createAppInfo(this->appName, this->engineName);
    VkInstanceCreateInfo instanceInfo = createInstanceInfo(appInfo, this->extensionAdapter,this->useValidation);

    if (vkCreateInstance(&instanceInfo,nullptr,&this->context.Instance)!=VK_SUCCESS) {
        throw InstanceInitializationError(VULK_INSTANCE_INITIALIZATION_ERROR("Failed to create Vulk Context"));
    };
    if (this->useValidation ) {
        //*attach validation layer
        VulkanDebugMessenger debugMessenger;
        //enable Severity
        debugMessenger.enableSeverity(VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT);
        debugMessenger.enableSeverity(VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT);
        debugMessenger.enableSeverity(VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT);
        //enable types
        debugMessenger.enableType(VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT);
        debugMessenger.enableType(VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT);
        debugMessenger.enableType(VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT);
        const auto createInfo = debugMessenger.getCreateInfo();
        if (debugMessenger.CreateDebugUtilsMessengerEXT(this->context.Instance,&createInfo,nullptr,&this->context.debugMessenger)!=VK_SUCCESS) {
            throw std::runtime_error(VULK_RUNTIME_ERROR("Failed To Setup Debug Layer"));
        }
    }
    //pick device
    auto device = pickSuitablePhysicalDevice(getPhysicalDeviceList(this->context.Instance));
    if (device==VK_NULL_HANDLE) throw std::runtime_error(VULK_INSTANCE_INITIALIZATION_ERROR("Failed to create Vulk Context"));
    auto DeviceQueueFamilyList = getQueueFamilies(device);
    auto Indices = getGraphicsQueueFamilyIndices(DeviceQueueFamilyList);
    if (!Indices.isValidGraphicsFamily()) {
        this->dropContext();
        throw std::runtime_error(VULK_RUNTIME_ERROR("Failed to pick Graphics Queue in  Context."));
    }
    this->context.Device.physicalDevice = device;
    this->context.queueFamilyIndices = Indices;
    this->context.Device.deviceFeatures = getPhysicalDeviceFeatures(this->context.Device.physicalDevice);
    //Create Physical Device
    auto deviceQueueInfo = createDeviceQueueInfo(Indices);
    const auto logicalDeviceCreateInfo = createLogicalDeviceInfo(deviceQueueInfo,this->context.Device,this->useValidation,this->extensionAdapter.validationLayers);
    if (vkCreateDevice(this->context.Device.physicalDevice,&logicalDeviceCreateInfo,nullptr,&this->context.Device.logicalDevice)!=VK_SUCCESS) {
        const auto deviceCreateStatus = vkCreateDevice(this->context.Device.physicalDevice,&logicalDeviceCreateInfo,nullptr,&this->context.Device.logicalDevice);
        std::cerr<<"Device Creation Failed:  "<<deviceCreateStatus<<std::endl;
        this->dropContext();
        throw std::runtime_error(VULK_RUNTIME_ERROR("Logical Device Creation Failed"));
    }
    //TODO: GET DEVICE QUEUE CREATED BY LOGICAL DEVICE

}








void VulkContext::dropContext() {
    if (this->extensionAdapter.extensions.empty() && this->extensionAdapter.validationLayers.empty()) return;
    this->extensionAdapter.extensions.clear();
    this->extensionAdapter.validationLayers.clear();
    this->appName.clear();
    this->engineName.clear();
    if (this->useValidation) {
        VulkanDebugMessenger::DestroyDebugUtilsMessengerEXT(this->context.Instance, this->context.debugMessenger, nullptr);
        this->useValidation=false;
    }
    if (this->context.Device.logicalDevice!=VK_NULL_HANDLE)vkDestroyDevice(this->context.Device.logicalDevice,nullptr);
    if (this->context.Instance!=VK_NULL_HANDLE)vkDestroyInstance(this->context.Instance,nullptr);
    this->context.Instance=VK_NULL_HANDLE;
}
