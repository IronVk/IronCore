//
// Created by adnan on 6/30/25.
//

#ifndef VULKINSTANCE_H
#define VULKINSTANCE_H
#include <string>
#include <vector>
#include <vulkan/vulkan.h>
#include <optional>

VkApplicationInfo createAppInfo(std::string appName,std::string engineName);

VkInstanceCreateInfo
createInstanceInfo(const VkApplicationInfo &appInfo, const std::vector<const char *> &requiredExtensions, std::optional<std::vector<const char *>> layers=std::nullopt);


#endif //VULKINSTANCE_H
