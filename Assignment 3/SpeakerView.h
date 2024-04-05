#ifndef SPEAKERVIEW_H
#define SPEAKERVIEW_H

#include "MonoStack.h"
#include "SpeakerView.h"
#include <iostream>
#include <fstream>
#include <string>

class SpeakerView{
    public:
        SpeakerView(std::string filename);
        virtual ~SpeakerView();
    private:
        int columns;
        int rows;
};
#endif