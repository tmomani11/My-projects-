#ifndef SPEAKERVIEW_H
#define SPEAKERVIEW_H

#include "MonoStack.h"
#include "SpeakerView.h"
#include <iostream>
#include <fstream>
#include <string>

class SpeakerView{
    public:
        SpeakerView();  //constructor
        virtual ~SpeakerView(); //destructor
        void ProcessFile(std::string file); // ProcessFile method
    private:
        int columns; //number of columns
        int rows;    // number of rows
};
#endif