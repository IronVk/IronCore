//
// Created by adnan on 7/1/25.
//

#include "VulkValidateInstance.h"
#include <cstring>
#include <vector>
#include <iostream>
#include <vulkan/vulkan.h>
#include "../Util/diagnostic/VULK_Diagnostic.h"
//TODO: search this function call through full code base...
bool checkInstanceExtensionSupport(const std::vector<const char *> *inputExtensionList) {
    uint32_t extCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extCount, nullptr);
    std::vector<VkExtensionProperties> extensionHolder =  std::vector<VkExtensionProperties>(extCount);
    vkEnumerateInstanceExtensionProperties(nullptr,&extCount,extensionHolder.data());

    for (const auto &current_extension : *inputExtensionList) {
        auto found = false;
        for (const auto &ext:extensionHolder ) {
            if (strcmp(ext.extensionName, current_extension) == 0) {
                found = true;
                break;
            }
        }
        if (!found) {
            std::cerr << VULK_NOT_FOUND_ERROR("Extension Not Found")<<current_extension<< std::endl;
            return found;
        }
    }

    return true;
}


bool checkValidationLayerSupport(const std::vector<const char *> *providedValidationLayer) {
    uint32_t validation_layer_count = 0;
    vkEnumerateInstanceLayerProperties(&validation_layer_count, nullptr);
    if (validation_layer_count<1)return false;
    std:: vector<VkLayerProperties> available_layers(validation_layer_count);
    vkEnumerateInstanceLayerProperties(&validation_layer_count, available_layers.data());
    for (const auto &current_layer: *providedValidationLayer) {
        for (const auto &layer:available_layers) {
            if (strcmp(current_layer,layer.layerName)==0)return true;
        }
    }
    return false;

}
