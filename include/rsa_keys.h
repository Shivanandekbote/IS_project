#ifndef RSA_KEYS_H
#define RSA_KEYS_H

#include <string>
#include <cryptopp/secblock.h>

// Generates RSA public and private keys
void generateRSAKeys(const std::string &publicKeyFile, const std::string &privateKeyFile);

// Encrypts an AES key and IV using RSA
void encryptAESKey(const CryptoPP::SecByteBlock &key, const CryptoPP::SecByteBlock &iv, 
                   const std::string &publicKeyFile, const std::string &outputKeyFile);

// Decrypts an AES key and IV using RSA
void decryptAESKey(CryptoPP::SecByteBlock &key, CryptoPP::SecByteBlock &iv, 
                   const std::string &privateKeyFile, const std::string &inputKeyFile);

#endif // RSA_KEYS_H
