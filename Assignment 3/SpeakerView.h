#ifndef SPEAKERVIEW_H
#define SPEAKERVIEW_H

#include "MonoStack.h"
#include "SpeakerView.h"
#include <iostream>
#include <fstream>
#include <string>

class SpeakerView{
    public:
        SpeakerView(std::string filename);  //constructor
        virtual ~SpeakerView();    //destructor
    private:
        int columns; //number of columns
        int rows;    // number of rows
};
#endif