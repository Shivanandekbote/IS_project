#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <vector>
#include <string>

// Function to encrypt the image data using AES
void aes_encrypt(const std::vector<unsigned char>& input_data, 
                 std::vector<unsigned char>& output_data, 
                 const unsigned char* key);

// Function to decrypt the image data using AES
void aes_decrypt(const std::vector<unsigned char>& input_data, 
                 std::vector<unsigned char>& output_data, 
                 const unsigned char* key);

#endif  // ENCRYPTION_H
