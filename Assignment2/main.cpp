#include "World.h"
#include "FileIO.h"
#include <iostream>

const int NUM_OF_SPECS = 8;

int main(int argc, char* argv[]){
    FileIO* file = new FileIO();
    if(argc < 3){
        std::cout << "Invalid number of arguments.\n";
        return -1;
    }

    int specs[NUM_OF_SPECS];
    if(!file->readFile(argv[1], specs)){
        std::cout << "Unable to read specs file.\n";
        return -1;
    }


    World* worldGame = new World(specs, argv[2]);
    if(!worldGame->start()){
        std::cout << "Unable to start simulation.\n";
        return -1;
    }
delete worldGame;
delete file;
    return 0;
}