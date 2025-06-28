//
// Created by adnan on 6/27/25.
//
#pragma once
#ifndef VULK_H
#define VULK_H
#include "Essentials/VulkInstanceInitializer.h"

class Window;

class Vulk {
private:
    //!vulkan context
    VulkInstanceInitializer vkContext;

    //?Window Manager
    Window window;



public:
    Vulk(int window_width,int window_height,std::string window_title,std::string app_name,std::string engine_name) {
        this->window = Window(window_width, window_height, window_title);
       this->vkContext.init(std::move(app_name), std::move(engine_name),&this->window);

    }
    ~Vulk() {
        vkDestroyInstance(this->vkContext.getVulkanInstance(), nullptr);
    }
    Window& getWindow() {
        return this->window;
    }


};



#endif //VULK_H
