#include "MonoStack.h"
#include "SpeakerView.h"
#include <iostream>
using namespace std;

int main(int argc, char** argv){
  SpeakerView* s1 = new SpeakerView(argv[1]);
  delete s1;
  return 0;
}
