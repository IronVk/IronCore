//
// Created by adnan on 7/3/25.
//
#pragma once
#ifndef VULKCONFIG_H
#define VULKCONFIG_H
#include <iostream>
#include <vector>
#include <GLFW/glfw3.h>
typedef enum {
    DEV = 0,
    PROD = 1
} BuildMode;

typedef struct {
    //Severity
    bool enableSeverityVerbose;
    bool enableSeverityInfo;
    bool enableSeverityWarning;
    bool enableSeverityError;
    //type
    bool enableMessageTypeGeneral;
    bool enableMessageTypeValidation;
    bool enableMessageTypePerformance;
} Validation;

typedef struct {
    std::string window_title;
    std::string app_name;
    std::string engine_name;
    GLFWwindow* window;
    int window_width;
    int window_height;
    BuildMode build_mode;
    Validation vkValidate;
    std::vector<const char *> extensions;
    const char* fragShaderPath;
    const char* vertShaderPath;
} VulkConf;




#endif //VULKCONFIG_H
