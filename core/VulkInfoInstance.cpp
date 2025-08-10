//
// Created by adnan on 6/30/25.
//

#include "VulkInfoInstance.h"

#include "../Util/diagnostic/VULK_Diagnostic.h"
#include "VulkDebug.h"
#include "../common/VulkCommon.h"
#include "../Validation/VulkValidateInstance.h"
#include <exception>

VkApplicationInfo createAppInfo(std::string appName, std::string engineName) {
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = appName.c_str();
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = engineName.c_str();
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_2;
    appInfo.pNext=nullptr;
    return appInfo;
}

VkInstanceCreateInfo createInstanceInfo(const VkApplicationInfo &appInfo, ExtensionAdapter& extAdapter,bool enableValidation) {
    if (extAdapter.extensions.empty())throw std::runtime_error(VULK_RUNTIME_ERROR("Required Extension Not Found"));
    VkInstanceCreateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    info.pApplicationInfo = &appInfo;
    if (enableValidation)extAdapter.extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    if (!checkInstanceExtensionSupport(&extAdapter.extensions)) throw std::runtime_error(VULK_RUNTIME_ERROR("Required Extensions not supported"));
    info.enabledExtensionCount = static_cast<uint32_t>(extAdapter.extensions.size());
    info.ppEnabledExtensionNames = extAdapter.extensions.data();
    if (enableValidation) {
        if (!checkValidationLayerSupport(&extAdapter.validationLayers)) throw std::runtime_error(VULK_RUNTIME_ERROR("Validation Layers not supported"));
        info.enabledLayerCount = static_cast<uint32_t>(extAdapter.validationLayers.size());
        info.ppEnabledLayerNames = extAdapter.validationLayers.data();
    }else {
        info.enabledLayerCount = ZERO;
        info.ppEnabledLayerNames = nullptr;
    }
    info.pNext = nullptr;
    return info;
}

