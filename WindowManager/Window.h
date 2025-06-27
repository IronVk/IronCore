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
#include<vector>

class Window {
private:
    std::string _title;
    GLFWwindow* window;
    int width, height;
    uint32_t required_extension_count = 0;
    bool window_initialize_succeed = false;
    std::vector<std::function<void()>> tasklist;
    std::vector<const char*> ExtensionList;
    void default_intiializer(int width=800, int height=600,std::string title= "VulkTools Window");
    public:
    Window();
    Window(int width, int height);
    Window(int width, int height,std::string title);
    ~Window();
    GLFWwindow* getWindow();
    template<typename Func, typename... Args>
    void  onTick(Func func, Args... args) {
        if (!this->window_initialize_succeed)return;
        this->tasklist.push_back(std::bind(func, args...));
    }
    void launch();

    //getters
    std::vector<const char*>& getRequiredInstanceExtensionList();


};



#endif //WINDOW_H
