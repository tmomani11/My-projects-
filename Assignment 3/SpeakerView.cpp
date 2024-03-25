#include <iostream>
#include <fstream>
#include <string>
#include "MonoStack.h"
#include "SpeakerView.h"
using namespace std;

SpeakerView::SpeakerView(string intF){
    //Take file input
    //go line by line and push each into the array through iterating
    ifstream readfile(intF);
    string line;

    //get number of heights
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
    
    //get number of lines
    m_lines = 0;
    while(getline(readfile, line)){
        m_lines++;
    }


    readfile.clear();
    readfile.seekg(0);
    //create array
    MonoStack<double>* myStack = new MonoStack<double>(m_lines, 'd');
    int atCurrSpace = 0;
    int atNextSpace = 0;
    for(int i = 0; i < m_heights; ++i){
        readfile.clear();
        readfile.seekg(0);
        getline(readfile, line);
        for(int j = 0; j < m_lines; ++j){
                atNextSpace = line.find(' ', atCurrSpace);
                string c = line.substr(atCurrSpace, atNextSpace);
                double pHeight = stod(c);
                myStack->push(pHeight);
                getline(readfile, line);
        }
        cout << "In column " << i << " there are " << myStack->size() << " that can see. " << endl;
        int stackSize = myStack->size();
        cout << "Their heights are: ";
        for(int k = 0; k < stackSize; ++k){
            cout << myStack->pop();
            if(k != stackSize-1){
                cout << ", ";
            }
        }
        cout << " inches. " << endl;
        readfile.clear();
        readfile.seekg(0);
        getline(readfile, line);
        atCurrSpace = line.find(' ', atNextSpace);
    }
    delete myStack;
}
SpeakerView::~SpeakerView(){
    
}