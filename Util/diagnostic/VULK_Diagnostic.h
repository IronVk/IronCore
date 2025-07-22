//
// Created by adnan on 6/30/25.
//
#pragma once
#ifndef DIAGONISTIC_H
#define DIAGONISTIC_H
#include <sstream>
#include <string>
#include <vector>
#include <regex>

template<typename T>
std::string to_string_any(const T& value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

// Replaces each `${}` in the input string with next value in args
template<typename... Args>
std::string format_log(const std::string& x, Args&&... args) {
    std::vector<std::string> values = { to_string_any(std::forward<Args>(args))... };
    std::string result = x;
    std::regex placeholder(R"(\$\{\})");
    size_t index = 0;
    std::smatch match;

    while (std::regex_search(result, match, placeholder) && index < values.size()) {
        result = match.prefix().str() + values[index++] + match.suffix().str();
    }

    return result;
}

// The macro: wraps everything into a log
#define VLOG(x, ...) \
std::cout<<"VULK::info::$" << format_log(x, ##__VA_ARGS__) << std::endl;


#define VULK_RUNTIME_ERROR(msg) ("VULK::RUNTIME::ERROR::$" + std::string(msg))
#define VULK_LOGIC_ERROR(msg) ("VULK::LOGIC::ERROR::$" + std::string(msg))
#define VULK_NOT_FOUND_ERROR(msg) ("VULK::NOT_FOUND::ERROR::$" + std::string(msg))
#define VULK_OUT_OF_RANGE_ERROR(msg) ("VULK::OUT_OF_RANGE::ERROR::$" + std::string(msg))
#define VULK_INTERNAL_MESSAGE(msg) ("VULK::INTERNAL_MESSAGE::$" + std::string(msg))
#define VULK_INSTANCE_INITIALIZATION_ERROR(msg) ("VULK::INSTANCE_INITIALIZATION::ERROR::$" + std::string(msg))
#endif //DIAGONISTIC_H
