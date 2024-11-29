#include "file_handler.h"
#include <fstream>

std::string readFile(const std::string &filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) throw std::runtime_error("File not found: " + filePath);

    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

void writeFile(const std::string &filePath, const std::string &data) {
    std::ofstream file(filePath, std::ios::binary);
    if (!file) throw std::runtime_error("Unable to write to file: " + filePath);

    file.write(data.data(), data.size());
}
