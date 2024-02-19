/*
 * Tyler Momani
 * 2455776
 * momani@chapman.edu
 * CPSC 350-02
 * Assignment 1: Robber Language Translation
 */

#include "FileProcessor.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

FileProcessor::FileProcessor(){}
FileProcessor::~FileProcessor(){}

/* processFile()
 * takes input file,processes it according to model class and outputs to html file specified
 * Return: void
 * Parameters:
 *  string inputFile:   name of the file to read the input
 *  string outputFile:  name of the file to output to
 */
void FileProcessor::processFile(std::string inputFile,std::string outputFile) {
 std::ifstream fin;
 std::ofstream fout;
 std::stringstream buffer;
 std::string original;
 std::string rovarspraket;

 // Open input file
 fin.open(inputFile);
 if (!fin.is_open()) {
  std::cerr << "Error: Unable to open input file: " << inputFile << std::endl;
  return;
 }

 // Read the content of the input file into a stringstream
 buffer << fin.rdbuf();

 // Close the input file
 fin.close();

 // Get the original English text from the stringstream
 original = buffer.str();

 // Perform Rövarspråket translation using your Translator class or function
 rovarspraket = Translator::translateEnglishSentence(original);

 // Open output file
 fout.open(outputFile);
 if (!fout.is_open()) {
  std::cerr << "Error: Unable to open output file: " << outputFile << std::endl;
  return;
 }

 // Write HTML content to the output file
 fout << "<html>\n<head>\n<title>Rövarspråket Translation</title>\n</head>\n<body>\n";
 fout << "<p><b>Original English Text:</b></p>\n";
 fout << "<p>" << original << "</p>\n";
 fout << "<br>\n";
 fout << "<p><i>Rövarspråket Translation:</i></p>\n";
 fout << "<p><i>" << rovarspraket << "</i></p>\n";
 fout << "</body>\n</html>";

 // Close the output file
 fout.close();
}
