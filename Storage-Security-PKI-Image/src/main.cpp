#include <iostream>
#include <vector>
#include <string>
#include "file_io.h"
#include "encryption.h"
#define AES_BLOCK_SIZE 16
#include <openssl/aes.h>
#include <openssl/rand.h>

int main() {
    // Define file paths
    std::string input_image_path = "images/image.jpg";  // Input image file path
    std::string encrypted_image_path = "images/encrypted_image.jpg";  // Output encrypted file
    std::string decrypted_image_path = "images/decrypted_image.jpg";  // Output decrypted file

    // Vector to hold image data
    std::vector<unsigned char> image_data;

    // Step 1: Read the input image
    read_image(input_image_path, image_data);

    // AES encryption key (128-bit key for simplicity)
    unsigned char key[AES_BLOCK_SIZE] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                                         0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};

    // Vector to hold encrypted data
    std::vector<unsigned char> encrypted_data;

    // Step 2: Encrypt the image data
    aes_encrypt(image_data, encrypted_data, key);
    write_image(encrypted_image_path, encrypted_data);
    std::cout << "Image encrypted and saved to " << encrypted_image_path << std::endl;

    // Vector to hold decrypted data
    std::vector<unsigned char> decrypted_data;

    // Step 3: Decrypt the image data
    aes_decrypt(encrypted_data, decrypted_data, key);
    write_image(decrypted_image_path, decrypted_data);
    std::cout << "Image decrypted and saved to " << decrypted_image_path << std::endl;

    return 0;
}
