#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream inputFile("/Users/rootadmin/Desktop/Информатика/С++ /Homework2/Homework2/input.txt");
    std::string line;
    
    while (std::getline(inputFile, line)) {
        std::cout << line << std::endl;
    }
    
    inputFile.close();
    return 0;
}
