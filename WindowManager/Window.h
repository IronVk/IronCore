//
// Created by adnan on 6/27/25.
//
#pragma once
#ifndef WINDOW_H
#define WINDOW_H
#define GLFW_INCLUDE_VULKAN
#include <iostream>
#include <GLFW/glfw3.h>
#include<functional>
#include <utility>
#include<vector>

class Window {
private:
    std::string _title;
    GLFWwindow* window{};
    int width{}, height{};
    uint32_t required_extension_count = 0;
    bool window_initialize_succeed = false;
    std::vector<std::function<void()>> tasklist;
    std::vector<const char*> ExtensionList;
    void default_intiializer(int width=800, int height=600,std::string title= "VulkTools Window") {
        try {
            this->_title =  std::move(title);
            this->width = width;
            this->height = height;
            if (!glfwInit()) {
                throw std::runtime_error("VulkTools GLFW initialization failed");
                return;
            }
            this->window = glfwCreateWindow(this->width, this->height, this->_title.c_str(), nullptr, nullptr);
            if (!this->window) {
                throw std::runtime_error("VulkTools Failed to create GLFW window");
            }
            glfwWindowHint(GLFW_CLIENT_API,GLFW_NO_API);
            glfwWindowHint(GLFW_RESIZABLE,GLFW_FALSE);
            this->window_initialize_succeed = true;
            //initialize vulkan helpers
            const char** required_extensions = glfwGetRequiredInstanceExtensions(&this->required_extension_count);
            std::vector<const char*> extensionList(required_extensions,required_extensions + this->required_extension_count);
            this->ExtensionList = std::move(extensionList);
        }catch (std::exception& e) {
            std::cout<<"VulkTool WinManager Failed: " << e.what() << std::endl;
        }
    }
    public:
    Window(){
        this->default_intiializer(800,600,"VulkTools Window");
    }
    Window(const int width,const int height){
        this->default_intiializer(width,height,"VulkTools Window");
    }
    Window(const int width,const int height, const std::string &title) {
        this->default_intiializer(width,height,title);
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

    ~Window(){
        this->destroy();
    }

    GLFWwindow *getWindow() {
        if (!this->window_initialize_succeed) throw std::runtime_error("WindowManager is not ready yet");
        return this->window;
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
            for (auto &task: this->tasklist) {
                try {
                    task();
                }catch (std::exception &e) {
                    const auto what = e.what();
                    std::cout<<"WindowManager Encountered Error: "<<what<<"\n";
                }
            }
        }
    }

    //getters
    std::vector<const char*>& getRequiredInstanceExtensionList() {
        return this->ExtensionList;
    }


};



#endif //WINDOW_H
