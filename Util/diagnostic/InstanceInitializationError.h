//
// Created by adnan on 7/2/25.
//
#pragma once
#ifndef INSTANCEINITIALIZATIONERROR_H
#define INSTANCEINITIALIZATIONERROR_H
#include <stdexcept>

#include "VULK_Diagnostic.h"

class InstanceInitializationError : public std::exception {
private:
    std::string message;
public:
    explicit InstanceInitializationError(const std::string& message) : message(VULK_INSTANCE_INITIALIZATION_ERROR(message)) {}
    [[nodiscard]] const char* what() const noexcept override {
        return this->message.c_str();
    }
};

#endif //INSTANCEINITIALIZATIONERROR_H
