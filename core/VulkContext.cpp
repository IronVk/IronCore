//
// Created by adnan on 6/30/25.
//

#include "VulkContext.h"

#include <iostream>
#include "VulkDebug.h"
#include "VulkDevice.h"
#include "VulkInfoInstance.h"
#include "../Util/diagnostic/InstanceInitializationError.h"

VulkContext::VulkContext() {
    this->useValidation = false;
    this->appName = "default";
    this->engineName = "VulkEngine";
    this->context.Instance = VK_NULL_HANDLE;
    this->context.Device.physicalDevice = VK_NULL_HANDLE;

}

VulkContext::~VulkContext() {
    this->dropContext();
}


void VulkContext::createContext() {
    if (this->appName.empty() || this->engineName.empty() || this->requiredExtensions.empty()) throw InstanceInitializationError("Required Info Missing to create Vulk Context");
    auto appInfo = createAppInfo(this->appName, this->engineName);
    auto instanceInfo = this->useValidation?
    createInstanceInfo(appInfo, this->requiredExtensions,this->validation_layer):
    createInstanceInfo(appInfo, this->requiredExtensions,std::nullopt);
    if (vkCreateInstance(&instanceInfo,nullptr,&this->context.Instance)!=VK_SUCCESS) {
        throw InstanceInitializationError(VULK_INSTANCE_INITIALIZATION_ERROR("Failed to create Vulk Context"));
    };
    std::cout << "Vulk error decode outer-phase 1"<< std::endl;
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
        auto createInfo = debugMessenger.getCreateInfo();
        debugMessenger.CreateDebugUtilsMessengerEXT(this->context.Instance,&createInfo,nullptr,&this->context.debugMessenger);
    }
    //pick device
    auto device = pickSuitablePhysicalDevice(getPhysicalDeviceList(this->context.Instance));
    if (device==VK_NULL_HANDLE) throw InstanceInitializationError(VULK_INSTANCE_INITIALIZATION_ERROR("Failed to create Vulk Context"));
    auto DeviceQueueFamilyList = getQueueFamilies(device);
    auto Indices = getGraphicsQueueFamilyIndices(DeviceQueueFamilyList);
    if (Indices.isValidGraphicsFamily()) {
        this->context.Device.physicalDevice = device;
        this->context.queueFamilyIndices = Indices;
        return;
    }
    this->dropContext();
    throw std::runtime_error(VULK_RUNTIME_ERROR("Could Not Create Context"));

}




void VulkContext::setAppName(std::string appName) {
    this->appName = appName;
}
void VulkContext::setEngineName(std::string engineName) {
    this->engineName = engineName;
}

void VulkContext::setRequiredExtensions(std::vector<const char *>& requiredExtensions) {
    this->requiredExtensions = requiredExtensions;
}

void VulkContext::enableValidation() {
    this->useValidation=true;
}

void VulkContext::disableValidation() {
    this->useValidation=false;
}

void VulkContext::dropContext() {
    if (this->context.Instance!=VK_NULL_HANDLE)vkDestroyInstance(this->context.Instance,nullptr);
    this->context.Device.physicalDevice = VK_NULL_HANDLE;
    this->context.Instance=VK_NULL_HANDLE;
}
