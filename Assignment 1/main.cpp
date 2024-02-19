/*
 * Tyler Momani
 * 2455776
 * momani@chapman.edu
 * CPSC 350-01
 * Assignment 1: Robber Language Translation
 */
#include "FileProcessor.h"
#include <iostream>
using namespace std;

int main(int argv, char* argc[]){

    if(argv < 3) {
        cout << "Incorrect number of arguments, give a file name to read from and a file name to output to." << endl;
        return -1;
    }

    FileProcessor *fp = new FileProcessor();
    fp->processFile(argc[1],argc[2]);



    return 0;
}