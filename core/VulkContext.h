//
// Created by adnan on 6/30/25.
//
#pragma once
#ifndef VULKCONTEXT_H
#define VULKCONTEXT_H
#include <string>
#include "../app/conf/VulkConfig.h"
#include "../common/VulkPredefs.h"
#include "../pipeline/Graphics/GraphicsPipeline.h"

class VulkContext {
private:
    VulkConf applicationConf;
    AppContext context;
    DisplayAdapter displayAdapter;
    QueueList queueList;
    std::string appName;
    std::string engineName;
    bool useValidation;
    ExtensionAdapter extensionAdapter;
    GraphicsPipeline graphicsPipeline;
    // helper functions
    void acquireDeviceQueues();
    void setupDebugLayer();

    //shader compilation

public:
    VulkContext(const VulkConf& vulk_conf) ;
    ~VulkContext();
    void dropContext();
    void createContext();
    void setupSwapChain();
    void createGraphicsPipeline();
    AppContext& getContext();
    MainDevice& getDevice();
};



#endif //VULKCONTEXT_H


