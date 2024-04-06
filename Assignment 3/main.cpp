#include "SpeakerView.h"
#include <iostream>

int main(int argc, char *argv[]){

  SpeakerView* speaker = new SpeakerView();
  speaker->ProcessFile(argv[1]);
  delete speaker;


  return 0;
}
