#include "encryption.h"
#include <openssl/aes.h>
#include <iostream>
#include <cstring>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
void aes_encrypt(const std::vector<unsigned char>& input_data, 
                 std::vector<unsigned char>& output_data, 
                 const unsigned char* key) {
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE] = {0};  // Initialization vector (use a fixed IV for simplicity)

    // Set AES encryption key
    if (AES_set_encrypt_key(key, 128, &aes_key) < 0) {
        std::cerr << "Error setting AES encryption key." << std::endl;
        return;
    }

    // Resize the output data to match the size of input data
    output_data.resize(input_data.size());

    // Perform AES encryption in CBC mode
    AES_cbc_encrypt(input_data.data(), output_data.data(), input_data.size(), &aes_key, iv, AES_ENCRYPT);
}

void aes_decrypt(const std::vector<unsigned char>& input_data, 
                 std::vector<unsigned char>& output_data, 
                 const unsigned char* key) {
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE] = {0};  // Initialization vector (use a fixed IV for simplicity)

    // Set AES decryption key
    if (AES_set_decrypt_key(key, 128, &aes_key) < 0) {
        std::cerr << "Error setting AES decryption key." << std::endl;
        return;
    }

    // Resize the output data to match the size of input data
    output_data.resize(input_data.size());

    // Perform AES decryption in CBC mode
    AES_cbc_encrypt(input_data.data(), output_data.data(), input_data.size(), &aes_key, iv, AES_DECRYPT);
}

// Function to generate RSA keys
void generateRSAKeys(const char* private_key_filename, const char* public_key_filename) {
    int bits = 2048;
    unsigned long exp = RSA_F4;

    RSA* rsa = RSA_generate_key(bits, exp, nullptr, nullptr);

    // Save the private key
    FILE* private_key_file = fopen(private_key_filename, "wb");
    PEM_write_RSAPrivateKey(private_key_file, rsa, nullptr, nullptr, 0, nullptr, nullptr);
    fclose(private_key_file);

    // Save the public key
    FILE* public_key_file = fopen(public_key_filename, "wb");
    PEM_write_RSA_PUBKEY(public_key_file, rsa);
    fclose(public_key_file);

    RSA_free(rsa);
}

