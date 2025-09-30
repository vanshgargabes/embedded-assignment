#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <openssl/evp.h>
#include <openssl/aes.h>

std::vector<uint8_t> hexToBytes(const std::string& hex) {
    std::vector<uint8_t> bytes;
    for (size_t i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        uint8_t byte = (uint8_t) strtol(byteString.c_str(), nullptr, 16);
        bytes.push_back(byte);
    }
    return bytes;
}

std::string bytesToHex(const std::vector<uint8_t>& data) {
    std::ostringstream oss;
    for (auto b : data) oss << std::hex << std::setw(2) << std::setfill('0') << (int)b;
    return oss.str();
}

std::vector<uint8_t> aes128Decrypt(const std::vector<uint8_t>& key,
                                   const std::vector<uint8_t>& iv,
                                   const std::vector<uint8_t>& ciphertext) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    std::vector<uint8_t> plaintext(ciphertext.size() + AES_BLOCK_SIZE);
    int len, plaintext_len;
    EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), nullptr, key.data(), iv.data());
    EVP_DecryptUpdate(ctx, plaintext.data(), &len, ciphertext.data(), ciphertext.size());
    plaintext_len = len;
    EVP_DecryptFinal_ex(ctx, plaintext.data() + len, &len);
    plaintext_len += len;
    plaintext.resize(plaintext_len);
    EVP_CIPHER_CTX_free(ctx);
    return plaintext;
}

int main() {
    std::string keyHex = "4255794d3dccfd46953146e701b7db68";
    std::string telegramHex =
        "a144c5142785895070078c20607a9d00902537ca231fa2da5889be8df367"
        "3ec136aebfb80d4ce395ba98f6b3844a115e4be1b1c9f0a2d5ffbb92906aa388deaa"
        "82c929310e9e5c4c0922a784df89cf0ded833be8da996eb5885409b6c9867978dea"
        "24001d68c603408d758a1e2b91c42ebad86a9b9d287880083bb0702850574d7b51"
        "e9c209ed68e0374e9b01febfd92b4cb9410fdeaf7fb526b742dc9a8d0682653";

    std::vector<uint8_t> key = hexToBytes(keyHex);
    std::vector<uint8_t> telegram = hexToBytes(telegramHex);

    std::vector<uint8_t> iv(16, 0);
    for (size_t i = 0; i < iv.size() && i < telegram.size(); i++) iv[i] = telegram[i];

    std::vector<uint8_t> ciphertext(telegram.begin() + iv.size(), telegram.end());

    std::vector<uint8_t> plaintext = aes128Decrypt(key, iv, ciphertext);

    std::cout << "Decrypted Payload (HEX): " << bytesToHex(plaintext) << std::endl;
    return 0;
}
