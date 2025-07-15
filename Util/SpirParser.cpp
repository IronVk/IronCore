//
// Created by STHEP on 7/16/2025.
//

#include "SpirParser.h"
#include <vector>
#include <ostream>
std::vector<char> SpirParser::parseSpirV(const std::string &file_path) {
    FILE *file = fopen(file_path.c_str(), "rb");
    if (!file) {
        throw std::runtime_error("Failed to open file");
    }
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        throw std::runtime_error("Failed to seek to end of file");
    }
    long size = ftell(file);
    if (size == -1) {
        fclose(file);
        throw std::runtime_error("Failed to get file size");
    }
    if (fseek(file, 0, SEEK_SET) != 0) {
        fclose(file);
        throw std::runtime_error("Failed to seek to beginning of file");
    }
    std::vector<char> buffer(size);
    size_t readSize = fread(buffer.data(), 1, size, file);
    fclose(file);

    if (readSize != static_cast<size_t>(size)) {
        throw std::runtime_error("Failed to read complete file");
    }
    return buffer;
}

