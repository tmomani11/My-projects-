#include "MonoStack.h"
#include "SpeakerView.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[]){
  string inputfile = "sampleInput.txt";
  SpeakerView* s1 = new SpeakerView(inputfile);
  delete s1;
  return 0;
}
