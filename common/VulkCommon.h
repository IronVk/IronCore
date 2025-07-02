//
// Created by adnan on 6/30/25.
//
#pragma once
#ifndef VULKCOMMON_H
#define VULKCOMMON_H
#include <vulkan/vulkan.h>

typedef struct {
    int graphicsFamilyIndex;
    bool isValidGraphicsFamily() const {
        return graphicsFamilyIndex >=0;
    }
} QueueFamilyIndices;

// type to hold device related infos
typedef  struct {
    VkPhysicalDevice physicalDevice;
    VkDevice logicalDevice;
} MainDevice;



typedef struct {
    VkInstance Instance;
    MainDevice Device;
    VkDebugUtilsMessengerEXT debugMessenger;
    QueueFamilyIndices queueFamilyIndices;
} VkContext;



#endif //VULKCOMMON_H
