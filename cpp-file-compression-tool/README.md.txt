# C++ File Compression Tool

This is a **C++ console application** that implements a simple **file compression tool** using the **Run-Length Encoding (RLE)** algorithm. The program allows users to **compress** and **decompress** text files, reducing file sizes by encoding consecutive characters into (character, count) pairs.

## Features
- **Compression**: Compresses a text file using the Run-Length Encoding algorithm.
- **Decompression**: Decompresses the RLE-compressed file back to its original form.
- **Command-Line Interface**: Simple and easy-to-use CLI for users.

## How to Use

### Prerequisites
Before you begin, make sure you have **g++** (GNU Compiler Collection) installed on your system to compile and run C++ code. If you don't have it, you can install it from [here](https://gcc.gnu.org/).

### Compiling the Code
To compile the program, open your terminal and run the following command in the folder where `main.cpp` is located:

```bash
g++ -o compressor main.cpp

This will generate an executable file called compressor (or compressor.exe on Windows).

Running the Program
Once the program is compiled, you can use it from the command line.

Compressing a File:
To compress a text file using Run-Length Encoding, use the following command:
./compressor compress --input input.txt --output compressed.rle

input.txt: The file you want to compress.
compressed.rle: The name of the output compressed file.

Decompressing a File:
To decompress a previously compressed .rle file back to its original text file, use the following command:
./compressor decompress --input compressed.rle --output decompressed.txt

compressed.rle: The compressed file you want to decompress.
decompressed.txt: The name of the output decompressed file.

Example
Let's say you have a text file called input.txt with the following content:
aaaaabbbbbcccdde

Compress the file:
./compressor compress --input input.txt --output compressed.rle

The compressed.rle file will contain:
a5b5c3d2e1

Decompress the file:
./compressor decompress --input compressed.rle --output decompressed.txt

File Structure
The project consists of the following files:
cpp-file-compression-tool/
├── main.cpp           # C++ source code for file compression/decompression
└── README.md          # Project description and instructions
