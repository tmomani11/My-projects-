#include <iostream>
#include <sstream>
#include "MonoStack.h"
#include "SpeakerView.h"
// constructor
SpeakerView::SpeakerView() {
    columns = 0;  // Initialize the number of columns to 0
    rows = 0;     // Initialize the number of rows to 0
}
// destructor
SpeakerView::~SpeakerView() = default;

/**
 * Processes a given file to analyze speaker heights and see if they have visibility of the speaker.
 *
 * This function opens and reads through a file line by line to count the number of rows and
 * validate the structure of the data. It then creates MonoStack instances to process
 * and output the number of speakers visible in each column along with their heights.
 *
 * @param file The path to the input file containing speaker height data.
 * @return void
 */
void SpeakerView::ProcessFile(std::string file) {
    std::ifstream readfile(file);  // Open the input file using the provided file path
    if (!readfile) {
        std::cerr << "Failed to open file: " << file << std::endl;  // Error message if file cannot be opened
        return;
    }
    std::string line;
    int firstLineColumns = 0;  // Variable to store the number of columns found in the first line
    while (getline(readfile, line)) {  // Read each line of the file
        std::stringstream ss(line);
        double value;
        int columnCount = 0;  // Counter for the number of values (columns) in the current line
        while (ss >> value) {
            columnCount++;  // Increment column counter for each value read
        }
        if (rows == 0) {
            firstLineColumns = columnCount;  // Initialize the number of columns based on the first line
        } else if (columnCount != firstLineColumns) {
            std::cerr << "Error: The structure of the file must remain a rectangle.Issue row "
                      << rows + 1 << "." << std::endl;
            return;
        }
        rows++;
    }
    columns = firstLineColumns;
    MonoStack<double> *dstack = new MonoStack<double>(rows, 'd');
    MonoStack<double> *output = new MonoStack<double>();

    readfile.clear();
    readfile.seekg(0, std::ios::beg);
    for (int i = 0; i < columns; ++i) {
        for (int j = 0; j < rows; ++j) {  // Iterate over each row for the current column
            getline(readfile, line);  // Read the current line
            std::stringstream ss(line);
            double height;
            for (int k = 0; k <= i; ++k) {  // Iterate up to the current column
                ss >> height;
            }
            dstack->push(height);
        }
        int size = dstack->size();  // Get the number of visible speakers in the current column
        std::cout << "In column " << i << " there are " << size << " that can see. ";
        std::cout << "Their heights are: ";
        while (!dstack->isEmpty()) {
            output->push(dstack->pop());
        }
        for (int k = 0; k < size; ++k) {
            std::cout << output->pop();
            if (k != size - 1) {
                std::cout << ", ";
            }
        }
        std::cout << " inches." << std::endl;
        readfile.clear();
        readfile.seekg(0, std::ios::beg);
    }
    delete dstack;
    delete output;
    readfile.close();
}
