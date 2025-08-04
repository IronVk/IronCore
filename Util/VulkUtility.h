//
// Created by adnan on 7/2/25.
//
#pragma once

#ifndef VULKUTILITY_H
#define VULKUTILITY_H
#define IS_SET_BIT(number,bit)(((number) & (1<<(bit))) != 0
#include <vector>

template<typename T>
void clearVector(const T& data) {
    std::vector<T>().swap(data);
}

#endif //VULKUTILITY_H
