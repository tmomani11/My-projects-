
/*
It checks if the arguments are != 2, and returns -1. If false, then it creates a new ServiceCenter object
with the parameters of the filename. It then calls ServiceCenter->printResult() where it will print out the 6 results
- Average Wait Time per Student for each Office
- Longest Wait Time for each Office
- Number of Students Waiting over 10 Min
- Average Window Idle Time
- Longest Window Idle Time
- Number of Windows Idle Over 5 Min
*/

#include "ServiceCenter.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    if (argc != 2) return -1;
    ServiceCenter *serviceCenter = new ServiceCenter(argv[1]);
    serviceCenter->printResult();
}