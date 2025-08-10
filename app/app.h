//
// Created by adnan on 7/2/25.
//
#pragma once
#ifndef APP_H
#define APP_H
#define VULK_VERSION 0.1
#if defined(IRON_VK_USE_SDL)
    #include "../external/glfw/WindowManager.h"
#else
    #include "../external/sdl/WindowManager.h"
#endif

#include "../core/VulkContext.h"
#include "conf/VulkConfig.h"

class app {
private:
    VulkConf createConfStruct;
    VulkContext* appContext;
    WindowManager* window_manager;
public:
    //! test check implementation
    app();
    ~app();
    VulkConf& getCreateConfStruct();
    void setConfig(VulkConf config);
    void build();


};



#endif //APP_H
