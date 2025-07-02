//
// Created by adnan on 6/30/25.
//

#include "VulkInfoInstance.h"

#include <iostream>
#include <optional>
#include <ostream>

#include "../Util/diagnostic/VULK_Diagnostic.h"
#include <stdexcept>

#include "VulkDebug.h"
#include "../Validation/VulkValidateInstance.h"


VkApplicationInfo createAppInfo(std::string appName, std::string engineName) {
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = appName.c_str();
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = engineName.c_str();
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_2;
    return appInfo;
}

VkInstanceCreateInfo createInstanceInfo(const VkApplicationInfo &appInfo, std::vector<const char *> &requiredExtensions, std::optional<std::vector<const char *>> layers) {
    if (requiredExtensions.empty())throw std::runtime_error(VULK_RUNTIME_ERROR("Required Extension Not Found"));
    VkInstanceCreateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    info.pApplicationInfo = &appInfo;
    if (layers.has_value())requiredExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    info.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
    info.ppEnabledExtensionNames = requiredExtensions.data();
    if (layers.has_value() ) {
        if (!checkValidationLayerSupport(&layers.value())) throw std::runtime_error(VULK_RUNTIME_ERROR("Validation Layers not supported"));
        info.enabledLayerCount = static_cast<uint32_t>(layers.value().size());
        info.ppEnabledLayerNames = layers.value().data();
    }else {
        info.enabledLayerCount = 0;
        info.ppEnabledLayerNames = nullptr;
    }
    if (!checkInstanceExtensionSupport(&requiredExtensions)) throw std::runtime_error(VULK_RUNTIME_ERROR("Required Extensions not supported"));

    return info;
}

