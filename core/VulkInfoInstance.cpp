//
// Created by adnan on 6/30/25.
//

#include "VulkInfoInstance.h"
#include "../Util/VULK_Diagnostic.h"
#include <stdexcept>


VkApplicationInfo createAppInfo(std::string appName, std::string engineName) {
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = std::move(appName).c_str();
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = std::move(engineName).c_str();
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_2;
    return appInfo;
}

VkInstanceCreateInfo createInstanceInfo(VkApplicationInfo &appInfo, const std::vector<const char *> &requiredExtensions, std::vector<const char *> &layers) {
    if (requiredExtensions.empty())throw std::runtime_error(VULK_RUNTIME_ERROR("Required Extension Not Found"));
    VkInstanceCreateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    info.pApplicationInfo = &appInfo;
    info.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
    info.ppEnabledExtensionNames = requiredExtensions.data();
    if (!layers.empty()) {
        info.enabledLayerCount = static_cast<uint32_t>(layers.size());
        info.ppEnabledLayerNames = layers.data();
    }else {
        info.enabledLayerCount = 0;
        info.ppEnabledLayerNames = nullptr;
    }
    return info;
}
