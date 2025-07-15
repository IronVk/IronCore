//
// Created by STHEP on 7/16/2025.
//
#pragma once
#ifndef SPIRPARSER_H
#define SPIRPARSER_H
#include <vector>
#include <string>


class SpirParser {
public:
    static std::vector<char> parseSpirV(const std::string &file_path);
};



#endif //SPIRPARSER_H
