#include "encryption.h"
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <fstream>

void encryptFile(const std::string &inputFile, const std::string &outputFile, const std::string &publicKeyFile) {
    CryptoPP::AutoSeededRandomPool prng;
    
    // Generate AES key and IV
    CryptoPP::SecByteBlock key(CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::SecByteBlock iv(CryptoPP::AES::BLOCKSIZE);
    prng.GenerateBlock(key, key.size());
    prng.GenerateBlock(iv, iv.size());

    // Encrypt data
    CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption aesEncryptor(key, key.size(), iv);
    std::ifstream input(inputFile, std::ios::binary);
    std::ofstream output(outputFile, std::ios::binary);

    CryptoPP::FileSource fs(input, true,
                            new CryptoPP::StreamTransformationFilter(aesEncryptor,
                                                                     new CryptoPP::FileSink(output)));

    // Encrypt AES key using RSA
    encryptAESKey(key, iv, publicKeyFile, outputFile + ".key");
}

void decryptFile(const std::string &encryptedFile, const std::string &outputFile, const std::string &privateKeyFile) {
    CryptoPP::SecByteBlock key(CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::SecByteBlock iv(CryptoPP::AES::BLOCKSIZE);

    // Decrypt AES key using RSA
    decryptAESKey(key, iv, privateKeyFile, encryptedFile + ".key");

    // Decrypt data
    CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption aesDecryptor(key, key.size(), iv);
    std::ifstream input(encryptedFile, std::ios::binary);
    std::ofstream output(outputFile, std::ios::binary);

    CryptoPP::FileSource fs(input, true,
                            new CryptoPP::StreamTransformationFilter(aesDecryptor,
                                                                     new CryptoPP::FileSink(output)));
}
