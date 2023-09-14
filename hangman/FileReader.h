#pragma once

#include <fstream>
#include <iostream>
#include <random>
#include <string>

class FileReader
{
private:
    std::string filePath{};
    std::string fileName{};
    std::ifstream fileStream;
    
    void resetFile()
    {
        fileStream.clear();
        fileStream.seekg(0,std::ios::beg);
    }

public:
    FileReader(std::string_view path, std::string_view name);
    ~FileReader();

    // get number of lines in file
    int getLineCount();

    // get line in file according to line number
    std::string getLine(int lineNumber /*=0*/ );

    // get random line in file
    std::string getRandomLine();

    // print file content
    void printFile();
};

