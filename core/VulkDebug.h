//
// Created by adnan on 6/30/25.
//

#ifndef VULKDEBUG_H
#define VULKDEBUG_H
#include <vector>
#include "../Util/diagnostic/VULK_Diagnostic.h"
#include <string>
#include <cstring>
#include <vulkan/vulkan.h>
#include <iostream>
#include "../common/VulkPredefs.h"

class VulkanDebugMessenger {
private:
    VkDebugUtilsMessageSeverityFlagsEXT enabledSeverities = ZERO;
    VkDebugUtilsMessageTypeFlagsEXT enabledTypes = ZERO;

public:

    void enableAllDebugLayers() {
        VLOG("DEBUG_VULKAN::ENABLING_ALL_DEBUG_LAYERS");
        this->enableSeverity(VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT);
        this->enableSeverity(VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT);
        this->enableSeverity(VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT);
        this->enableSeverity(VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT);
        //enable types
        this->enableType(VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT);
        this->enableType(VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT);
        this->enableType(VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT);
    }

    // Enable specific message severity
    void enableSeverity(VkDebugUtilsMessageSeverityFlagBitsEXT severity) {
        enabledSeverities |= severity;
    }

    bool has_ValidationLayerSupport(const std::vector<const char *>& inputExtensionList){
        u32 validation_layer_count = ZERO;
        vkEnumerateInstanceLayerProperties(&validation_layer_count, nullptr);
        if (validation_layer_count<ONE)return false;
        std:: vector<VkLayerProperties> available_layers(validation_layer_count);
        vkEnumerateInstanceLayerProperties(&validation_layer_count, available_layers.data());
        for (const auto &current_layer: inputExtensionList) {
            for (const auto &layer:available_layers) {
                if (strcmp(current_layer,layer.layerName)==0)return true;
            }
        }
        return false;

    }


    // Disable specific message severity
    void disableSeverity(VkDebugUtilsMessageSeverityFlagBitsEXT severity) {
        enabledSeverities &= ~severity;
    }

    // Enable specific message type
    void enableType(VkDebugUtilsMessageTypeFlagBitsEXT type) {
        enabledTypes |= type;
    }

    // Disable specific message type
    void disableType(VkDebugUtilsMessageTypeFlagBitsEXT type) {
        enabledTypes &= ~type;
    }

    // Get the current severity flags
    VkDebugUtilsMessageSeverityFlagsEXT getEnabledSeverities() const {
        return enabledSeverities;
    }

    // Get the current type flags
    VkDebugUtilsMessageTypeFlagsEXT getEnabledTypes() const {
        return enabledTypes;
    }

    // Static callback function for Vulkan
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData)
    {
        VulkanDebugMessenger* self = static_cast<VulkanDebugMessenger*>(pUserData);
        if ((messageSeverity & self->enabledSeverities) &&
            (messageType & self->enabledTypes)) {
            std::cerr << VULK_INTERNAL_MESSAGE(pCallbackData->pMessage) << std::endl;
        }
        return VK_FALSE;
    }

    // Get the raw function pointer
    PFN_vkDebugUtilsMessengerCallbackEXT getCallback() const {
        return debugCallback;
    }

    // Create and return a VkDebugUtilsMessengerCreateInfoEXT struct
    VkDebugUtilsMessengerCreateInfoEXT getCreateInfo() {
        VkDebugUtilsMessengerCreateInfoEXT createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.pNext = nullptr;
        createInfo.flags = ZERO;
        createInfo.messageSeverity = enabledSeverities;
        createInfo.messageType = enabledTypes;
        createInfo.pfnUserCallback = debugCallback;
        createInfo.pUserData = this; // Pass pointer to this instance
        return createInfo;
    }

    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr) {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        } else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    static void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr) {
            func(instance, debugMessenger, pAllocator);
        }
    }
};




#endif //VULKDEBUG_H
