#include <iostream>
#include <fstream>
#include <string>

std::string convertToColumnTitle(int n) {
    std::string result = "";
    while (n > 0) {
        int rem = (n - 1) % 26;
        result = char('A' + rem) + result;
        n = (n - 1) / 26;
    }
    return result;
}

int main() {
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");

    if (!inputFile) {
        std::cerr << "Error opening input file." << std::endl;
        return 1;
    }

    if (!outputFile) {
        std::cerr << "Error opening output file." << std::endl;
        return 1;
    }

    int i;
    while (inputFile >> i) {
        std::string columnTitle = convertToColumnTitle(i);
        outputFile << columnTitle << std::endl;
    }

    inputFile.close();
    outputFile.close();

    return 0;
}