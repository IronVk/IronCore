//
// Created by adnan on 6/28/25.
//

#ifndef VULKINSTACEINITIALIZER_H
#define VULKINSTACEINITIALIZER_H
#include <iostream>
#include <vector>
#include <vulkan/vulkan_core.h>
#include <vulkan/vulkan.h>

#include "../../WindowManager/Window.h"

class Window;

class VulkInstanceInitializer {
private:
    VkInstance instance{};
    std::string appName;
    std::string EngineName;
    uint32_t appVersion{};
    uint32_t engineVersion{};
    uint32_t apiVersion{};
    Window* window;
    bool validateExtensions(std::vector<const char*>* inputExtensionList);

public:
    VulkInstanceInitializer()=default;
    void init(std::string appName,std::string engine_name, Window* win) {
        if (!win)throw std::invalid_argument("Window is null");
        this->window = win;
        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = std::move(appName).c_str();
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = std::move(engine_name).c_str();
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_2;
        //?creating instance
        VkInstanceCreateInfo vkIns{};
        vkIns.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        vkIns.pApplicationInfo = &appInfo;
        if (!this->validateExtensions(&this->window->getRequiredInstanceExtensionList())) {
            throw std::runtime_error("Invalid extension list");
        }
        vkIns.enabledExtensionCount = this->window->getRequiredInstanceExtensionList().size();
        vkIns.ppEnabledExtensionNames = this->window->getRequiredInstanceExtensionList().data();
        if (vkCreateInstance(&vkIns,nullptr,&this->instance)!=VK_SUCCESS) {
            throw std::runtime_error("Failed to create vulkan instance");
        }
        std::printf("Instance Initialization Succeed");

    }
    VkInstance& getVulkanInstance() {
        return this->instance;
    }


};



#endif //VULKINSTACEINITIALIZER_H
