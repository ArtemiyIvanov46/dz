#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

class CSVTable {
private:
    int N, M;
    std::vector<std::vector<int>> data;

public:
    bool loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            return false;
        }
        std::string firstLine;
        std::getline(file, firstLine);
        std::istringstream iss(firstLine);
        iss >> N >> M;

        data.resize(N, std::vector<int>(M));
        std::string line;
        int row = 0;

        while (std::getline(file, line) && row < N) {
            std::istringstream lineStream(line);
            std::string cell;
            int col = 0;

            while (std::getline(lineStream, cell, ',') && col < M) {
                data[row][col] = std::stoi(cell);
                col++;
            }
            row++;
        }

        file.close();
        return true;
    }

    void printTable() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                std::cout << std::setw(10) << data[i][j];
                
                if (j < M - 1) {
                    std::cout << " ";
                }
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    CSVTable table;
    
    if (table.loadFromFile("/Users/rootadmin/Desktop/Информатика/С++ /Homework2/Homework 2.1.3/input3.txt")) {
        table.printTable();
    } else {
        std::cerr << "Не удалось открыть файл input.txt" << std::endl;
        return 1;
    }
    
    return 0;
}
