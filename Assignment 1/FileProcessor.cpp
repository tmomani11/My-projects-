#include "FileProcessor.h"
#include <string>
#include <fstream>
#include <iostream>

FileProcessor::FileProcessor(){}  // default constructor
FileProcessor::~FileProcessor(){} // default destructor

/*
 * The processFile function reads from an input file, processes the content according to the Translator class,
 * and writes the translated content to an output file in HTML format.
 *
 * @param inputFile: The name of the file to read the input from.
 * @param outputFile: The name of the file to write the output to.
 */
void FileProcessor::processFile(std::string inputFile, std::string outputFile) {

    std::string sentence;
    std::fstream my_file;
    std::string translatedSentence;
    std::ofstream outFile(outputFile);
    Translator t;
    my_file.open(inputFile);

    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open output file: " << outputFile << std::endl;
        return;
    }
    outFile << "<!DOCTYPE html>\n";
    outFile << " <html> <head> <title> Robbers Translation </title> </head> <body>"  << std::endl;


    if (!my_file.is_open()) {
        std::cerr << "Error: Unable to open input file: " << inputFile << std::endl;
        return;
    }
    while(getline(my_file,sentence) && !sentence.empty())
    {
        outFile << "<p><b>" << sentence << "</b></p>\n";
        std::string translated = t.translateEnglishSentence(sentence);
        translatedSentence += "<br>" + translated + "<br>\n";
    }
    outFile << "<p><i>" << translatedSentence << "</i></p>" << std::endl;
    outFile << "</body> </html>" << std::endl;

    my_file.close();
    outFile.close();

}