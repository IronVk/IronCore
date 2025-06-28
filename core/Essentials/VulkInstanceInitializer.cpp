//
// Created by adnan on 6/28/25.
//

#include "VulkInstanceInitializer.h"
#include <vulkan/vulkan.h>
#include <cstring>
bool VulkInstanceInitializer::validateExtensions(std::vector<const char *>* inputExtensionList) {
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
            std::cerr << "VkInstanceError: Extension " << current_extension << " not found!" << std::endl;
            return found;
        }
    }

    return true;
}

