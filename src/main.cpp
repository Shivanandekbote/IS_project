#include <iostream>
#include "encryption.h"
#include "rsa_keys.h"
#include "file_handler.h"
#include "utilities.h"

int main() {
    try {
        std::string inputFile = "../data/input_image.jpg";
        std::string encryptedFile = "../data/encrypted_image.dat";
        std::string decryptedFile = "../data/decrypted_image.jpg";

        std::string publicKeyFile = "../data/rsa_public_key.pem";
        std::string privateKeyFile = "../data/rsa_private_key.pem";

        // Generate RSA keys
        generateRSAKeys(publicKeyFile, privateKeyFile);

        // Encrypt the file
        encryptFile(inputFile, encryptedFile, publicKeyFile);

        // Decrypt the file
        decryptFile(encryptedFile, decryptedFile, privateKeyFile);

        std::cout << "Encryption and decryption completed successfully!" << std::endl;

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
