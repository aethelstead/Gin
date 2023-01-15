#include <iostream>
#include <fstream>
#include <sstream>
#include "file.h"

bool Gin::Platform::read_file(const char* filePath, std::string& outFileText)
{
    outFileText.clear();

    std::ifstream inFile;
    inFile.open(filePath);
    if (inFile.fail())
        return false;

    std::stringstream ss;
    ss << inFile.rdbuf();

    inFile.close();

    outFileText += ss.str();

    return true;
}
