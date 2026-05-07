#include <iostream>
#include "encoder.h"

int main() {

    const size_t BUFFER_SIZE = 4096;
    char inPath[BUFFER_SIZE];
    char outPath[BUFFER_SIZE];
    char keyStr[BUFFER_SIZE];

    std::cout << "Enter input file path: ";
    std::cin.getline(inPath, BUFFER_SIZE);
    if (std::cin.fail()) {
        std::cout << "Error reading input path.\n";
        return 1;
    }

    std::cout << "Enter output file path: ";
    std::cin.getline(outPath, BUFFER_SIZE);
    if (std::cin.fail()) {
        std::cout << "Error reading output path.\n";
        return 1;
    }

    std::cout << "Enter key (string): ";
    std::cin.getline(keyStr, BUFFER_SIZE);
    if (std::cin.fail()) {
        std::cout << "Error reading key.\n";
        return 1;
    }

    size_t keyLen = std::strlen(keyStr);
    if (keyLen == 0 || keyLen > 256) {
        std::cout << "Invalid key length (must be 1..256).\n";
        return 1;
    }

    encoder enc(reinterpret_cast<unsigned char*>(keyStr), keyLen);

    std::cout << "Encrypting...\n";
    if (!enc.encode(inPath, outPath, true)) {
        std::cout << "Encryption failed.\n";
        return 1;
    }
    std::cout << "Encryption done.\n";

    char decPath[BUFFER_SIZE];
    std::cout << "Enter path for decrypted file: ";
    std::cin.getline(decPath, BUFFER_SIZE);
    if (std::cin.fail()) {
        std::cout << "Error reading decrypt path.\n";
        return 1;
    }

    std::cout << "Decrypting...\n";
    if (!enc.encode(outPath, decPath, true)) {
        std::cout << "Decryption failed.\n";
        return 1;
    }
    std::cout << "Decryption done. Compare files.\n";

    return 0;
}


// /Users/admin/Desktop/СPP/_1/encoder/files/PT12.docx
// /Users/admin/Desktop/СPP/_1/encoder/files/output.rtf
// /Users/admin/Desktop/СPP/_1/encoder/files/dec.docx

// /Users/admin/Desktop/ПЗ12.docx 
// /Users/admin/Desktop/output.rtf
// /Users/admin/Desktop/dec.docx 
