//
// Created by adnan on 6/27/25.
//

#include "Window.h"

Window::Window() {
    this->default_intiializer(800,600,"VulkTools Window");
}

Window::Window(int width, int height) {
    this->default_intiializer(width,height,"VulkTools Window");
}

Window::Window(int width, int height, std::string title) {
    this->default_intiializer(width,height,title);
}

void Window::default_intiializer(int width, int height,std::string title) {
    this->_title =  title;
    this->width = width;
    this->height = height;
    this->window = glfwCreateWindow(this->width, this->height, this->_title.c_str(), nullptr, nullptr);
    glfwWindowHint(GLFW_CLIENT_API,GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE,GLFW_FALSE);
    this->window_initialize_succeed = true;
    //initialize vulkan helpers
    const char** required_extensions = glfwGetRequiredInstanceExtensions(&this->required_extension_count);
    std::vector<const char*> extensionList(required_extensions,required_extensions + this->required_extension_count);
    this->ExtensionList = std::move(extensionList);
}

std::vector<const char *> &Window::getRequiredInstanceExtensionList() {
    return this->ExtensionList;
}

GLFWwindow* Window::getWindow() {
    return this->window;
}



