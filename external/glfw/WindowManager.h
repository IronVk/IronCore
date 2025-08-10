//
// Created by adnan on 7/2/25.
//
#ifndef IRON_VK_USE_SDL
#pragma once
#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H
#define GLFW_INCLUDE_VULKAN
#include "../../Util/diagnostic/VULK_Diagnostic.h"
#include <GLFW/glfw3.h>
#include <bits/this_thread_sleep.h>
#include <functional>
#include <iostream>
#include <stdio.h>
#include <utility>
#include <vector>

class WindowManager {
private:
    std::string _title;
    GLFWwindow* window{};
    int width{}, height{};
    int WindowScreenWidth;
    int WindowScreenHeight;
    uint32_t required_extension_count = 0;
    bool window_initialize_succeed = false;
    std::vector<std::function<void()>> tasklist;
    std::vector<const char*> ExtensionList;
    void default_initializer(int width=800, int height=600,std::string title= "VulkTools Window") {
        try {
            this->_title =  std::move(title);
            this->width = width;
            this->height = height;
            if (!glfwInit()) {
                throw std::runtime_error("VulkTools GLFW initialization failed");
                return;
            }
            GLFWmonitor* monitor = glfwGetPrimaryMonitor();
            if (!monitor) {
                std::cerr << "Failed to get primary monitor\n";
                glfwTerminate();
                return;
            }
            const GLFWvidmode* mode = glfwGetVideoMode(monitor);
            glfwWindowHint(GLFW_CLIENT_API,GLFW_NO_API);
            this->window = glfwCreateWindow(this->width, this->height, this->_title.c_str(), nullptr, nullptr);
            if (!this->window) {
                std::cout << "VulkTools GLFW window creation failed"<<stderr << std::endl;
                glfwTerminate();
                throw std::runtime_error("VulkTools Failed to create GLFW window");
            }
            glfwSetWindowPos(this->window,200,200);
            glfwWindowHint(GLFW_RESIZABLE,GLFW_FALSE);
            glfwWindowHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
            this->WindowScreenWidth= mode->width;
            this->WindowScreenHeight= mode->height;
            this->window_initialize_succeed = true;
        }catch (std::exception& e) {
            std::cout<<"VulkTool WinManager Failed: " << e.what() << std::endl;
        }
    }

    void keyCallBacks() const;

public:
    WindowManager() {
        this->default_initializer(800,600,"VulkTools Window");
        if (!glfwVulkanSupported())throw std::runtime_error(VULK_RUNTIME_ERROR("Vulkan is not supported"));
        //initialize vulkan helpers
        const char** required_extensions = glfwGetRequiredInstanceExtensions(&this->required_extension_count);
        std::vector<const char*> extensionList(required_extensions,required_extensions + this->required_extension_count);
        this->ExtensionList = std::move(extensionList);
    }
    WindowManager(const int width,const int height){
        this->default_initializer(width,height,"VulkTools Window");
        //initialize vulkan helpers
        const char** required_extensions = glfwGetRequiredInstanceExtensions(&this->required_extension_count);
        std::vector<const char*> extensionList(required_extensions,required_extensions + this->required_extension_count);
        this->ExtensionList = std::move(extensionList);
    }
    WindowManager(const int width,const int height, const std::string &title) {
        this->default_initializer(width,height,title);
        //initialize vulkan helpers
        const char** required_extensions = glfwGetRequiredInstanceExtensions(&this->required_extension_count);
        std::vector<const char*> extensionList(required_extensions,required_extensions + this->required_extension_count);
        this->ExtensionList = std::move(extensionList);
    }
    ~WindowManager(){
        this->destroy();
    }
    GLFWwindow *getWindow() {
        if (!this->window_initialize_succeed) throw std::runtime_error("WindowManager is not ready yet");
        return this->window;
    }
    void destroy() {
        this->window_initialize_succeed = false;
        this->ExtensionList.clear();
        this->tasklist.clear();
        this->_title.clear();
        this->required_extension_count = 0;
        glfwDestroyWindow(this->window);
        glfwTerminate();
    }

    [[nodiscard]] int MonitorWidth() const {
        return  this->WindowScreenWidth;
    }

    [[nodiscard]] int MonitorHeight() const {
        return  this->WindowScreenHeight;
    }

    template<typename Func, typename... Args>
    void  onTick(Func func, Args... args) {
        if (!this->window_initialize_succeed)return;
        this->tasklist.push_back(std::bind(func, args...));
    }
    void launch(){
        if (!this->window_initialize_succeed) throw std::runtime_error("WindowManager is not ready yet");
        while (!glfwWindowShouldClose(this->getWindow())) {
            glfwPollEvents();
            this->keyCallBacks();
            for (auto &task: this->tasklist) {
                try {
                    task();
                }catch (std::exception &e) {
                    const auto what = e.what();
                    std::cerr<<"WindowManager Encountered Error: "<<what<<"\n";
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(33));
        }
    }

    //getters
    std::vector<const char*>& getRequiredInstanceExtensionList() {
        return this->ExtensionList;
    }

};



#endif //WINDOWMANAGER_H
#endif