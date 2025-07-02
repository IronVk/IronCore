//
// Created by adnan on 7/2/25.
//
#pragma once
#ifndef APP_H
#define APP_H
#define VULK_VERSION 0.1


#ifdef VULK_GLFW
#    include "../external/glfw/WindowManager.h"
#endif
#include "../core/VulkContext.h"

class app {
private:
    VulkContext appContext;

public:
    //! test check implementation
    app(std::vector<const char *> requiredExtensions) {
        this->appContext.setAppName("default");
        this->appContext.setRequiredExtensions(requiredExtensions);
        this->appContext.enableValidation();
        this->appContext.createContext();
    }
};



#endif //APP_H
