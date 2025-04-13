#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <bitset>

using namespace std;

// Huffman Tree Node
struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

// Comparison class for priority queue
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

// Generate Huffman codes
void generateCodes(Node* root, string code, unordered_map<char, string>& huffCode) {
    if (!root) return;
    if (!root->left && !root->right)
        huffCode[root->ch] = code;
    generateCodes(root->left, code + "0", huffCode);
    generateCodes(root->right, code + "1", huffCode);
}

// Build Huffman tree
Node* buildHuffmanTree(unordered_map<char, int>& freqMap) {
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto& pair : freqMap) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* merged = new Node('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;

        pq.push(merged);
    }
    return pq.top();
}

// Serialize Huffman tree (preorder)
void serializeTree(Node* root, string& out) {
    if (!root) return;
    if (!root->left && !root->right) {
        out += '1';
        out += root->ch;
    } else {
        out += '0';
        serializeTree(root->left, out);
        serializeTree(root->right, out);
    }
}

// Deserialize Huffman tree
Node* deserializeTree(string& data, int& index) {
    if (index >= data.size()) return nullptr;
    if (data[index] == '1') {
        index++;
        char ch = data[index++];
        return new Node(ch, 0);
    }
    index++;
    Node* left = deserializeTree(data, index);
    Node* right = deserializeTree(data, index);
    Node* node = new Node('\0', 0);
    node->left = left;
    node->right = right;
    return node;
}

// Encode and compress
void compress(string inputFile, string outputFile) {
    ifstream in(inputFile, ios::binary);
    ofstream out(outputFile, ios::binary);

    unordered_map<char, int> freq;
    string text;

    char ch;
    while (in.get(ch)) {
        freq[ch]++;
        text += ch;
    }

    Node* root = buildHuffmanTree(freq);
    unordered_map<char, string> huffCode;
    generateCodes(root, "", huffCode);

    string encoded = "";
    for (char c : text)
        encoded += huffCode[c];

    int padding = 8 - (encoded.size() % 8);
    if (padding != 8) {
        for (int i = 0; i < padding; i++) encoded += "0";
    } else {
        padding = 0;
    }

    string treeData = "";
    serializeTree(root, treeData);

    // Write padding and tree metadata
    out << padding << '\n';
    out << treeData.size() << '\n';
    out.write(treeData.c_str(), treeData.size());

    // Write encoded binary
    for (size_t i = 0; i < encoded.size(); i += 8) {
        bitset<8> bits(encoded.substr(i, 8));
        out.put(static_cast<unsigned char>(bits.to_ulong()));
    }

    in.close();
    out.close();
    cout << "File compressed successfully.\n";
}

// Decode and decompress
void decompress(string inputFile, string outputFile) {
    ifstream in(inputFile, ios::binary);
    ofstream out(outputFile, ios::binary);

    int padding, treeSize;
    string line;

    getline(in, line);
    padding = stoi(line);

    getline(in, line);
    treeSize = stoi(line);

    // Read Huffman tree
    string treeData(treeSize, '\0');
    in.read(&treeData[0], treeSize);

    int idx = 0;
    Node* root = deserializeTree(treeData, idx);

    // Read remaining binary data
    string bitStr = "";
    char byte;
    while (in.get(byte)) {
        bitStr += bitset<8>(static_cast<unsigned char>(byte)).to_string();
    }

    // Remove padding bits
    if (padding > 0)
        bitStr = bitStr.substr(0, bitStr.size() - padding);

    // Decode using tree
    Node* curr = root;
    for (char bit : bitStr) {
        curr = (bit == '0') ? curr->left : curr->right;
        if (!curr->left && !curr->right) {
            out << curr->ch;
            curr = root;
        }
    }

    in.close();
    out.close();
    cout << "File decompressed successfully.\n";
}

// Menu
int main() {
    int choice;
    string input = "input.txt";
    string compressed = "compressed.huff";
    string output = "output.txt";

    cout << "-------------------------------------------\n";
    cout << "| File Compression Using Huffman Encoding |\n";
    cout << "-------------------------------------------\n";
    cout << "1. Compress File\n";
    cout << "2. Decompress File\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1)
        compress(input, compressed);
    else if (choice == 2)
        decompress(compressed, output);
    else
        cout << "Invalid choice!\n";

    return 0;
}
