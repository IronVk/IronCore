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
    AppContext context;
    DisplayAdapter displayAdapter;
    QueueList queueList;
    std::string appName;
    std::string engineName;
    bool useValidation;
    ExtensionAdapter extensionAdapter;
    // helper functions
    void acquireDeviceQueues();
    void setupDebugLayer();
public:
    VulkContext(const VulkConf& vulk_conf) ;
    ~VulkContext();
    void dropContext();
    void createContext();
    void setupSwapChain();
    AppContext& getContext();
    MainDevice& getDevice();
};



#endif //VULKCONTEXT_H
