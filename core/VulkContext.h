//
// Created by adnan on 6/30/25.
//

#ifndef VULKCONTEXT_H
#define VULKCONTEXT_H
#include <string>
#include <vector>
#include <optional>
#include "VulkDebug.h"
#include "../app/conf/VulkConfig.h"
#include "../common/VulkCommon.h"


class VulkContext {
private:
    VkContext context;
    DisplayAdapter displayAdapter;
    std::string appName;
    std::string engineName;
    bool useValidation;
    ExtensionAdapter extensionAdapter;

public:
    VulkContext(VulkConf vulk_conf) ;
    ~VulkContext();
    void dropContext();
    void createContext();
    VkContext& getContext();
    MainDevice& getDevice();
};



#endif //VULKCONTEXT_H
