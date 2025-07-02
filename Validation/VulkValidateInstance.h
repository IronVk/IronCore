//
// Created by adnan on 7/1/25.
//
#pragma once
#ifndef VULKVALIDATEINSTANCEANDDEVICE_H
#define VULKVALIDATEINSTANCEANDDEVICE_H
#include <vector>



bool checkInstanceExtensionSupport(const std::vector<const char*>* inputExtensionList);
bool checkValidationLayerSupport(const std::vector<const char *> *providedValidationLayer) ;


#endif //VULKVALIDATEINSTANCEANDDEVICE_H
