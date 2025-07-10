//
// Created by adnan on 7/2/25.
//

#include "WindowManager.h"

void WindowManager::keyCallBacks() const {
    if (glfwGetKey(this->window,GLFW_KEY_ESCAPE)==GLFW_PRESS || glfwGetKey(this->window,GLFW_KEY_END)==GLFW_PRESS) {
        glfwSetWindowShouldClose(this->window,GLFW_TRUE);
    }
}
