//
// Created by adnan on 6/30/25.
//
#pragma once
#ifndef DIAGONISTIC_H
#define DIAGONISTIC_H

#define VULK_RUNTIME_ERROR(msg) ("VULK::RUNTIME::ERROR::$" + std::string(msg))
#define VULK_LOGIC_ERROR(msg) ("VULK::LOGIC::ERROR::$" + std::string(msg))
#define VULK_NOT_FOUND_ERROR(msg) ("VULK::NOT_FOUND::ERROR::$" + std::string(msg))
#define VULK_OUT_OF_RANGE_ERROR(msg) ("VULK::OUT_OF_RANGE::ERROR::$" + std::string(msg))
#define VULK_INTERNAL_ERROR(msg) ("VULK::INTERNAL_DETECTION::ERROR::$" + std::string(msg))

#endif //DIAGONISTIC_H
