//
// Created by adnan on 6/30/25.
//

#ifndef VULKDEBUG_H
#define VULKDEBUG_H
#include <vector>

#include "../Util/VULK_Diagnostic.h"

bool checkValidationLayerSupport(const std::vector<const char*>& inputExtensionList);

#include <vulkan/vulkan.h>
#include <iostream>
#include <string>
#include <bitset>
#include <functional>
#include <cstring>
#include <vulkan/vulkan.h>
#include <iostream>
#include <string>

class VulkanDebugMessenger {
private:
    VkDebugUtilsMessageSeverityFlagsEXT enabledSeverities = 0;
    VkDebugUtilsMessageTypeFlagsEXT enabledTypes = 0;

public:
    // Enable specific message severity
    void enableSeverity(VkDebugUtilsMessageSeverityFlagBitsEXT severity) {
        enabledSeverities |= severity;
    }

    bool has_ValidationLayerSupport(const std::vector<const char *>& inputExtensionList){
        uint32_t validation_layer_count = 0;
        vkEnumerateInstanceLayerProperties(&validation_layer_count, nullptr);
        if (validation_layer_count<1)return false;
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
            std::cerr << VULK_INTERNAL_ERROR(pCallbackData->pMessage) << std::endl;
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
        createInfo.flags = 0;
        createInfo.messageSeverity = enabledSeverities;
        createInfo.messageType = enabledTypes;
        createInfo.pfnUserCallback = debugCallback;
        createInfo.pUserData = this; // Pass pointer to this instance
        return createInfo;
    }
};




#endif //VULKDEBUG_H
