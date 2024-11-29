#include "file_io.h"
#include <iostream>
#include <fstream>

void read_image(const std::string& file_path, std::vector<unsigned char>& image_data) {
    std::ifstream file(file_path, std::ios::binary);
    
    if (!file) {
        std::cerr << "Error: Unable to open file " << file_path << std::endl;
        return;
    }
    
    // Move the file pointer to the end to get the file size
    file.seekg(0, std::ios::end);
    size_t file_size = file.tellg();
    file.seekg(0, std::ios::beg);
    
    // Resize the vector to the file size
    image_data.resize(file_size);
    
    // Read the file into the vector
    file.read(reinterpret_cast<char*>(image_data.data()), file_size);
    file.close();
    
    std::cout << "File read successfully, size: " << image_data.size() << " bytes." << std::endl;
}

void write_image(const std::string& file_path, const std::vector<unsigned char>& image_data) {
    std::ofstream file(file_path, std::ios::binary);
    
    if (!file) {
        std::cerr << "Error: Unable to open file " << file_path << std::endl;
        return;
    }
    
    // Write the image data to the file
    file.write(reinterpret_cast<const char*>(image_data.data()), image_data.size());
    file.close();
    
    std::cout << "File written successfully to: " << file_path << std::endl;
}
