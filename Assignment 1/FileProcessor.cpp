#include "FileProcessor.h"
#include <string>
#include <fstream>
#include <iostream>

FileProcessor::FileProcessor(){}
FileProcessor::~FileProcessor(){}

/* processFile()
 * takes input file,processes it according to model class and outputs to html file specified
 * Return: void
 * Parameters:
 *  string inputFile:   name of the file to read the input
 *  string outputFile:  name of the file to output to
 */
void FileProcessor::processFile(std::string inputFile, std::string outputFile) {

    std::string sentence;
    std::fstream my_file;
    std::string translatedSentence;
    std::ofstream outFile(outputFile);

    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open output file: " << outputFile << std::endl;
        return;
    }
    outFile << "<!DOCTYPE html>\n";
    outFile << " <html> <head> <title> Robbers Translation </title> </head> <body>"  << std::endl;

    my_file.open(inputFile, std::ios::in);
    if (!my_file.is_open()) {
        std::cerr << "Error: Unable to open input file: " << inputFile << std::endl;
        return;
    }
    while(getline(my_file,sentence))
    {
        outFile << "<p><b>" << sentence << "</b></p>\n";

        // Translate the current sentence to Rövarspråket
        std::string translated = Translator::translateEnglishSentence(sentence);

        // Append the translated sentence to the overall translatedSentence
        translatedSentence += "<br>" + translated + "<br>\n";
    }

    outFile << "<p><i>" << translatedSentence << "</i></p>" << std::endl;
    outFile << "</body> </html>" << std::endl;

    my_file.close();
    outFile.close();

}