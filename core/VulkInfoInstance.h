//
// Created by adnan on 6/30/25.
//

#ifndef VULKINSTANCE_H
#define VULKINSTANCE_H
#include <iostream>
#include <vulkan/vulkan.h>
#include "../common/VulkCommon.h"

VkApplicationInfo createAppInfo(std::string appName,std::string engineName);

VkInstanceCreateInfo createInstanceInfo(const VkApplicationInfo &appInfo, ExtensionAdapter& extAdapter,bool enableValidation);


#endif //VULKINSTANCE_H
