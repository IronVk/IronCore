//
// Created by adnan on 6/30/25.
//

#ifndef VULKINSTANCE_H
#define VULKINSTANCE_H
#include <string>
#include <vector>
#include <vulkan/vulkan.h>


VkApplicationInfo createAppInfo(std::string appName,std::string engineName);

VkInstanceCreateInfo
createInstanceInfo(VkApplicationInfo &appInfo, const std::vector<const char *> &requiredExtensions, std::vector<const char *> &layers);


#endif //VULKINSTANCE_H
