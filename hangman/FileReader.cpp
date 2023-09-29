#include <cassert>
#include "FileReader.h"

FileReader::FileReader(std::string_view path, std::string_view name)
    : filePath{path}, fileName{name}
{
    fileStream.open(filePath + fileName);
    if(!fileStream){
        std::cerr << "This file does not exist!\n";
        exit(1);
    }
}

FileReader::~FileReader()
{
    fileStream.close();
}

int FileReader::getLineCount()
{
    resetFile();
    int count{0};
    std::string line{};
    while(std::getline(fileStream,line))
        ++count;
    return count;
}

std::string FileReader::getLine(int lineNumber=0)
{
    assert(lineNumber >= 0 && lineNumber < getLineCount());
    resetFile();
    std::string line{};
    for(int count{0}; count <= lineNumber; ++count)
    {
        std::getline(fileStream,line);
    }
    return line;
}

std::string FileReader::getRandomLine()
{
    // generate valid random line number in file
    std::random_device rd{};
    std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
    std::mt19937 mt{ ss }; // initialize mersenne twister with seed ss
    std::uniform_int_distribution lineNumberGenerator{ 0, getLineCount() - 1 };
    int randomLineNumber{lineNumberGenerator(mt)};
    return getLine(randomLineNumber);
}

void FileReader::printFile()
{
    resetFile();
    std::string line{};
    while(std::getline(fileStream,line))
        std::cout << line << '\n';
}

void FileReader::reopen(std::string_view path, std::string_view name)
{
    fileStream.close();
    fileStream.clear();
    filePath = path;
    fileName = name;
    fileStream.open(filePath + fileName);
    if(!fileStream){
        std::cerr << "This file does not exist!\n";
        exit(1);
    }
}

std::string FileReader::getPath() const
{
    return filePath + fileName;
}

std::string FileReader::getFileName() const
{
    return fileName;
}

