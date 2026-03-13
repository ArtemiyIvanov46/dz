#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream inputFile("/Users/rootadmin/Desktop/Информатика/С++ /Homework2/Homework 2.1.2/input2.txt");
    std::ofstream outputFile("/Users/rootadmin/Desktop/Информатика/С++ /Homework2/Homework 2.1.2/output.txt");
    std::string line;
    
    while (std::getline(inputFile, line)) {
        outputFile << line << std::endl;
    }
    
    inputFile.close();
    outputFile.close();
    return 0;
}
