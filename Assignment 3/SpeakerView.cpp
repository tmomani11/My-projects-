#include <iostream>
#include <string>
#include <sstream>
#include "MonoStack.h"    // Include the MonoStack class header
#include "SpeakerView.h"  // Include the SpeakerView class header

// SpeakerView class constructor
SpeakerView::SpeakerView() {
    columns = 0;  // Initialize columns to 0
    rows    = 0;     // Initialize rows to 0
}

// SpeakerView class destructor
SpeakerView::~SpeakerView() = default;

/**
 * Processes the given file to analyze speaker heights and determine which speakers
 * in each column can see the speaker in front of them based on their heights.
 *
 * This function reads through the file line by line, counts the total number of rows,
 * determines the number of columns based on the first line, and then for each column,
 * uses stacks to find out which speakers can "see" (based on heights comparison).
 *
 * @param file The path to the input file containing speaker height data.
 * @return void
 */
void SpeakerView::ProcessFile(std::string file){
    std::ifstream readfile(file);  // Open the input file
    std::string line;
    // Count the number of lines in the file to determine rows
    while (getline(readfile, line)) {
        rows++;
    }
    // Read the first line again to count the number of columns (assuming space-separated values)
    getline(readfile, line);
    std::stringstream ss(line);
    double value;
    while (ss >> value) {
        columns++;
    }

    // Create a stack for the current column and an output stack
    MonoStack<double> *dstack = new MonoStack<double>(rows, 'd');  // Stack for the current column
    MonoStack<double> *output = new MonoStack<double>();  // Stack for the output

    // Process each column
    for (int i = 0; i < columns; ++i) {
        // Reset file read pointer to the beginning
        readfile.clear();
        readfile.seekg(0);
        // Read each row in the current column
        for (int j = 0; j < rows; ++j) {
            getline(readfile, line);
            std::stringstream ss(line);
            // Read up to the current column
            for (int k = 0; k <= i; ++k) {
                ss >> value;
            }
            dstack->push(value);  // Push the height onto the stack
        }
        // Output the number of speakers that can see and their heights
        int size = dstack->size();
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
    }
    delete dstack;
    delete output;
}
