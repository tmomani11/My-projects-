#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include "Translator.h"
#include <string>


class FileProcessor{
public:
    FileProcessor();  // Default constructor
    virtual ~FileProcessor();  // Virtual destructor

    // Processes a file by reading from an input file, translating the content,
    // and writing the translated content to an output file.
    // @param inputFile The name of the file to read the input from.
    // @param outputFile The name of the file to write the output to.
    static void processFile(std::string inputFile,std::string outputFile);

private:

};

#endif