#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>
#include <cryptopp/secblock.h>

// Encrypts a file using AES and RSA
void encryptFile(const std::string &inputFile, const std::string &outputFile, const std::string &publicKeyFile);

// Decrypts a file using AES and RSA
void decryptFile(const std::string &encryptedFile, const std::string &outputFile, const std::string &privateKeyFile);

#endif // ENCRYPTION_H
