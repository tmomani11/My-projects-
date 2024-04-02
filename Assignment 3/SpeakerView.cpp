#include <iostream>
#include <fstream>
#include <string>
#include "MonoStack.h"
#include "SpeakerView.h"
using namespace std;

// Constructor for the SpeakerView class
// Takes a string parameter which is the name of the input file
SpeakerView::SpeakerView(string intF){
    // Open the input file
    ifstream readfile(intF);
    string line;

    // Count the number of heights in the first line of the file
    getline(readfile, line);
    m_heights = 0;
    for(int i = 0; i < line.length(); ++i){
        if(line[i] == ' '){
            m_heights++;
        }
    }
    m_heights++;
    readfile.clear();
    readfile.seekg(0);

    // Count the number of lines in the file
    m_lines = 0;
    while(getline(readfile, line)){
        m_lines++;
    }

    // Reset the file stream to the beginning of the file
    readfile.clear();
    readfile.seekg(0);

    // Create a new MonoStack object
    MonoStack<double>* myStack = new MonoStack<double>(m_lines, 'd');
    MonoStack<double> *outputStack = new MonoStack<double>();

    int atCurrSpace = 0;
    int atNextSpace = 0;
    // Loop over the number of heights
    for(int i = 0; i < m_heights; ++i){
        // Clear the file stream and reset it to the beginning of the file
        readfile.clear();
        readfile.seekg(0);
        // Read the first line of the file
        getline(readfile, line);
        // Loop over the number of lines in the file
        for(int j = 0; j < m_lines; ++j){
            // Find the next space in the line
            atNextSpace = line.find(' ', atCurrSpace);
            // Extract the substring from the current space to the next space
            string c = line.substr(atCurrSpace, atNextSpace);
            // Convert the substring to a double
            double pHeight = stod(c);
            // Push the height onto the stack
            myStack->push(pHeight);
            // Read the next line of the file
            getline(readfile, line);
        }

        while(!myStack->isEmpty()){
            outputStack->push(myStack->pop());
        }
        cout << "In column " << i << " there are " << myStack->size() << " that can see. ";
        int stackSize = outputStack->size();
        cout << "Their heights are: ";
        for(int k = 0; k < stackSize; ++k){
            cout << outputStack->pop();
            if(k != stackSize - 1){
                cout << ", ";
            }
        }
        cout << " inches. " << endl;



        // Clear the file stream and reset it to the beginning of the file
        readfile.clear();
        readfile.seekg(0);



        // Read the first line of the file
        getline(readfile, line);
        // Find the next space in the line
        atCurrSpace = line.find(' ', atNextSpace);
    }
    // Delete the MonoStack object
    delete outputStack;
    delete myStack;

}

// Destructor for the SpeakerView class
SpeakerView::~SpeakerView()= default;