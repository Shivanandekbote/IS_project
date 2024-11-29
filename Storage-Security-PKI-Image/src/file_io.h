#ifndef FILE_IO_H
#define FILE_IO_H

#include <vector>
#include <string>

// Function to read image from file
void read_image(const std::string& file_path, std::vector<unsigned char>& image_data);

// Function to write image to file
void write_image(const std::string& file_path, const std::vector<unsigned char>& image_data);

#endif  // FILE_IO_H
