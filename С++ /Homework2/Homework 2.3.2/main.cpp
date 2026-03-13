#include <iostream>
#include <fstream>
#include <string>

int main() {

    std::ifstream file("/Users/rootadmin/Desktop/Информатика/С++ /Homework2/Homework 2.3.2/2.bin", std::ios::binary);

    unsigned int size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));

    char ch;
    std::string key = "20241130WhySoSerious?";
    std::string kipher;

    while (file.get(ch)) {
        kipher += ch;
    }

    while (kipher.size() < key.size()) {
        kipher += '?';
    }

    std::string decoded;

    for (size_t i = 0; i < kipher.size(); i++) {
        decoded += kipher[i] ^ key[i % key.size()];
    }

    std::cout << decoded.substr(0, size);

    file.close();
}
//# Part 3
//Last file is encoded by symmetric algorithm. To get the name guess the riddle.
//Two letters at the start — they’re like friends,
//Four is the number that always blends.
//Together they form a code that keeps a secret,
//Name them quickly — don’t let the moment slip!

//Keyword is start of the phrase "..., but you merely adopted the dark.". (lowercase with commas and spaces).Program ended with exit code: 0
