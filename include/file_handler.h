#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <string>

// Reads the contents of a file and returns them as a string
std::string readFile(const std::string &filePath);

// Writes the given data to a file
void writeFile(const std::string &filePath, const std::string &data);

#endif // FILE_HANDLER_H
