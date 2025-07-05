//
// Created by adnan on 6/30/25.
//

#include "VulkSwapchain.h"

bool createSurface(VkInstance instance, GLFWwindow& window, VkSurfaceKHR& surface) {
    if (glfwCreateWindowSurface(instance,&window,nullptr,&surface)!=VK_SUCCESS) {
        throw std::runtime_error(VULK_RUNTIME_ERROR("Window Surface Creation Error"));
    }
    return true;
}
