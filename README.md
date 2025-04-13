# File-Compression-Using-Huffman-Encoding-in-DAA

## Project Overview

This project implements a **File Compression and Decompression** system using **Huffman Encoding**, a popular algorithm for lossless data compression. The algorithm is based on assigning shorter codes to more frequent characters and longer codes to less frequent characters, helping reduce the overall file size.

This project demonstrates the usage of **Trees** and **Linked Lists** in the implementation of Huffman Encoding and Decompression.

## Features

- **Compression**: Compresses a text file by encoding it with Huffman codes.
- **Decompression**: Decompresses the encoded file back to its original form using the Huffman tree.
- **Text File Input and Output**: Supports reading from a `.txt` file for compression and saving output to `.txt` for decompression.

## Tools & Technologies

- **Programming Language**: C++
- **IDE**: Code::Blocks / Visual Studio Code / Turbo C++
- **Data Structures**:
  - **Binary Trees** (Huffman Tree)
  - **Priority Queue** (Min Heap using STL)
  - **Hash Map** (for frequency and code mapping)
- **File Formats**: `.txt`, `.huff`

## Algorithm Overview

1. **Frequency Calculation**: Calculate the frequency of each character in the input file.
2. **Huffman Tree Construction**: Build a priority queue and iteratively combine nodes to form the Huffman Tree.
3. **Code Generation**: Traverse the Huffman Tree to generate binary codes for each character.
4. **Compression**: Encode the input file using the generated Huffman codes and store metadata (tree structure and padding) for later use.
5. **Decompression**: Read the metadata and binary data, rebuild the Huffman tree, and decode the binary data back into the original text.

## Steps for Compression and Decompression

### Compression:
1. Input a `.txt` file (e.g., `input.txt`).
2. The program calculates the frequency of each character.
3. It then builds the Huffman Tree and generates the Huffman codes.
4. The encoded data is saved in a `.huff` file along with metadata (tree structure and padding).

### Decompression:
1. Input a `.huff` file containing the encoded data.
2. The program extracts the Huffman Tree and binary data.
3. The binary data is decoded using the Huffman Tree, and the original file is reconstructed and saved as `output.txt`.

## Usage

1. **Compress a File:**

   - Run the program and choose option **1** (Compress File).
   - Enter the name of the input file (e.g., `input.txt`).
   - The program will generate a compressed `.huff` file.

2. **Decompress a File:**

   - Run the program and choose option **2** (Decompress File).
   - Enter the name of the compressed file (e.g., `compressed.huff`).
   - The program will output the decompressed file as `output.txt`.

## Example

**Before Compression:**

- `input.txt`: A text file containing the text "This is an example of Huffman Encoding".

**After Compression:**

- `compressed.huff`: A binary-encoded file with Huffman codes and tree metadata.

**After Decompression:**

- `output.txt`: The original text file is restored: "This is an example of Huffman Encoding".

## Future Enhancements

- Support for compressing image and audio files.
- Custom binary file formats for more efficient storage.
- GUI-based compression tool using frameworks like Qt or Python.

## References

- Cormen, Leiserson, Rivest – *Introduction to Algorithms*.
- GeeksForGeeks – [www.geeksforgeeks.org](https://www.geeksforgeeks.org).
- TutorialsPoint – [www.tutorialspoint.com](https://www.tutorialspoint.com).
- YouTube: SimpleSnippets, CodeWithHarry (for C++ DSA tutorials).

## Author

- **Name**: [Sharad Kalathiya].
* https://www.linkedin.com/in/sharadkalathiya/ 
