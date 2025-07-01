//
// Created by adnan on 6/30/25.
//

#ifndef VULKCONTEXT_H
#define VULKCONTEXT_H
#include <string>
#include <vector>

#include "../common/VulkCommon.h"


class VulkContext {
private:
    VkContext context;
    MainDevice device;
    std::string appName;
    std::string engineName;
    std::vector<const char *> requiredExtensions;
    void __intialize_vulkan__context();
public:
    VulkContext();
    ~VulkContext();
    void setAppName(std::string appName);
    void setEngineName(std::string engineName);
    void setRequiredExtensions(std::vector<const char *> requiredExtensions);
    VkContext& getContext();
    [[nodiscard]] const VkContext& getReadOnlyContext() const;
};



#endif //VULKCONTEXT_H
