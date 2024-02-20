#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include "Translator.h"
#include <string>

class FileProcessor{
    public:
        FileProcessor();
        virtual ~FileProcessor();
        static void processFile(std::string inputFile,std::string outputFile);

    private:

};

#endif