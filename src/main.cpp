#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "JSON.h"

std::string readFileToString(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Failed to open file: " + filename);
    }
    std::ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main() {
    try {
        std::string filename = "./json.txt";
        std::string content = readFileToString(filename);

        JSON* j = new JSON(content);
        std::cout << j->getValue<std::string>("primitive") << std::endl;
        delete j;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}