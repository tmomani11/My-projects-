#include "World.h"
#include "FileIO.h"
#include <iostream>
using namespace std;

const int NUM_OF_SPECS = 8;

int main(int argc, char* argv[]){
    if(argc < 3){
        cout << "Invalid number of arguments.\n";
        return -1;
    }

    int specs[NUM_OF_SPECS];
    if(!FileIO::readFile(argv[1], specs, NUM_OF_SPECS)){
        cout << "Unable to read specs file.\n";
        return -1;
    }


    World worldGame(specs, argv[2]);
    if(!worldGame.start()){
        cout << "Unable to start simulation.\n";
        return -1;
    }

    return 0;
}