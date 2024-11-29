#include "rsa_keys.h"
#include <cryptopp/rsa.h>
#include <cryptopp/osrng.h>
#include <cryptopp/files.h>

void generateRSAKeys(const std::string &publicKeyFile, const std::string &privateKeyFile) {
    CryptoPP::AutoSeededRandomPool rng;
    CryptoPP::RSA::PrivateKey privateKey;
    CryptoPP::RSA::PublicKey publicKey;

    privateKey.GenerateRandomWithKeySize(rng, 2048);
    publicKey.AssignFrom(privateKey);

    CryptoPP::FileSink pubFile(publicKeyFile.c_str());
    publicKey.Save(pubFile);

    CryptoPP::FileSink privFile(privateKeyFile.c_str());
    privateKey.Save(privFile);
}

void encryptAESKey(const CryptoPP::SecByteBlock &key, const CryptoPP::SecByteBlock &iv, 
                   const std::string &publicKeyFile, const std::string &outputKeyFile) {
    CryptoPP::RSA::PublicKey publicKey;
    CryptoPP::FileSource file(publicKeyFile.c_str(), true);
    publicKey.Load(file);

    CryptoPP::AutoSeededRandomPool rng;
    CryptoPP::RSAES_OAEP_SHA_Encryptor encryptor(publicKey);

    CryptoPP::SecByteBlock combined(key.size() + iv.size());
    memcpy(combined, key, key.size());
    memcpy(combined + key.size(), iv, iv.size());

    CryptoPP::FileSink fs(outputKeyFile.c_str());
    CryptoPP::ArraySource(combined, combined.size(), true,
                          new CryptoPP::PK_EncryptorFilter(rng, encryptor, new CryptoPP::Redirector(fs)));
}

void decryptAESKey(CryptoPP::SecByteBlock &key, CryptoPP::SecByteBlock &iv, 
                   const std::string &privateKeyFile, const std::string &inputKeyFile) {
    CryptoPP::RSA::PrivateKey privateKey;
    CryptoPP::FileSource file(privateKeyFile.c_str(), true);
    privateKey.Load(file);

    CryptoPP::AutoSeededRandomPool rng;
    CryptoPP::RSAES_OAEP_SHA_Decryptor decryptor(privateKey);

    CryptoPP::FileSource fs(inputKeyFile.c_str(), true,
                            new CryptoPP::PK_DecryptorFilter(rng, decryptor,
                                                             new CryptoPP::ArraySink(reinterpret_cast<byte *>(&key), key.size())));
    memcpy(iv, key + CryptoPP::AES::DEFAULT_KEYLENGTH, CryptoPP::AES::BLOCKSIZE);
}
