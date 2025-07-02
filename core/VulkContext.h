//
// Created by adnan on 6/30/25.
//

#ifndef VULKCONTEXT_H
#define VULKCONTEXT_H
#include <string>
#include <vector>
#include <optional>
#include "VulkDebug.h"
#include "../common/VulkCommon.h"


class VulkContext {
private:
    VkContext context;
    std::string appName;
    std::string engineName;
    bool useValidation;
    std::optional<std::vector<const char *>> validation_layer = std::make_optional<std::vector<const char*>>({ "VK_LAYER_KHRONOS_validation"});
    std::vector<const char *> requiredExtensions;

public:
    VulkContext();
    ~VulkContext();
    void dropContext();
    void createContext();
    void setAppName(std::string appName);
    void setEngineName(std::string engineName);
    void enableValidation();
    void disableValidation();
    void setRequiredExtensions(std::vector<const char *>& requiredExtensions);
    VkContext& getContext();
    MainDevice& getDevice();
};



#endif //VULKCONTEXT_H
