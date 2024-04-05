#include <iostream>
#include <string>
#include "MonoStack.h"
#include "SpeakerView.h"
using namespace std;

// Constructor for the SpeakerView class
SpeakerView::SpeakerView(string filename) {
   unsigned int atSpace   = 0;
   unsigned int nextSpace = 0;
    columns               = 1;
    rows                  = 0;
    ifstream readfile(filename); // Open the input file
    string line;

    // Get the number of rows
    while (getline(readfile, line)) { // Count the number of lines in the file
        rows++;
    }
    // Get the number of columns
    getline(readfile, line);
    for (char i: line) { // Count the number of spaces in the first line
        if (i == ' ') {
            columns++;
        }
    }

    // Create stacks
    MonoStack<double> *stack = new MonoStack<double>(rows, 'd'); // Stack for the current column
    MonoStack<double> *output = new MonoStack<double>(); // Stack for the output
    for (int i = 0; i < columns; ++i) {
        readfile.clear();
        readfile.seekg(0);
        getline(readfile, line);
        for (int j = 0; j < rows; ++j) {
            nextSpace = line.find(' ', atSpace); // Find the next space
            string value = line.substr(atSpace,nextSpace); // Get the string between the current space// and the next space
            double personHeight = stod(value); // Convert the string to a double
            stack->push(personHeight); // Push the height onto the stack
            getline(readfile, line); // Read the next line
        }
        int size = stack->size();
        cout << "In column " << i << " there are " << size << " that can see. ";
        cout << "Their heights are: ";
        while (!stack->isEmpty()) {
            output->push(stack->pop());
        }
        for (int k = 0; k < size; ++k) {
            cout << output->pop();
            if (k != size - 1) {
                cout << ",";
            }
        }
        cout << " inches. " << endl;
        readfile.clear();
        readfile.seekg(0);
        getline(readfile, line);
        atSpace = line.find(' ', nextSpace); // Find the next space for the next column
    }
    delete stack;
    delete output;
}
// Destructor for the SpeakerView class
SpeakerView::~SpeakerView()= default;