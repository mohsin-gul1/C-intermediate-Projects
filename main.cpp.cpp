#include <iostream>
#include <fstream>
#include <string>

// Function to compress a file using Run-Length Encoding (RLE)
void compressFile(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream in(inputFile, std::ios::binary);
    std::ofstream out(outputFile, std::ios::binary);

    if (!in.is_open() || !out.is_open()) {
        std::cerr << "Error opening files!" << std::endl;
        return;
    }

    char prevChar = 0;
    int count = 0;

    while (in.get(prevChar)) {
        count = 1;
        while (in.peek() == prevChar && count < 255) {
            in.get(prevChar);
            count++;
        }
        out.put(prevChar);
        out.put(count);
    }

    in.close();
    out.close();
    std::cout << "File compressed successfully!" << std::endl;
}

// Function to decompress a file using Run-Length Encoding (RLE)
void decompressFile(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream in(inputFile, std::ios::binary);
    std::ofstream out(outputFile, std::ios::binary);

    if (!in.is_open() || !out.is_open()) {
        std::cerr << "Error opening files!" << std::endl;
        return;
    }

    char ch;
    char count;
    while (in.get(ch) && in.get(count)) {
        for (int i = 0; i < (unsigned char)count; ++i) {
            out.put(ch);
        }
    }

    in.close();
    out.close();
    std::cout << "File decompressed successfully!" << std::endl;
}

// Main function to handle command-line arguments and execute operations
int main(int argc, char* argv[]) {
    if (argc < 5) {
        std::cerr << "Usage: <operation> --input <input-file> --output <output-file>" << std::endl;
        return 1;
    }

    std::string operation = argv[1];
    std::string inputFile = argv[3];
    std::string outputFile = argv[4];

    if (operation == "compress") {
        compressFile(inputFile, outputFile);
    } else if (operation == "decompress") {
        decompressFile(inputFile, outputFile);
    } else {
        std::cerr << "Invalid operation! Use 'compress' or 'decompress'." << std::endl;
        return 1;
    }

    return 0;
}
