#ifndef SPEAKERVIEW_H
#define SPEAKERVIEW_H

#include "MonoStack.h"
#include "SpeakerView.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class SpeakerView{
    public:
        SpeakerView(string intF);
        virtual ~SpeakerView();

        
    private:
        int m_lines;
        int m_heights;
};


#endif