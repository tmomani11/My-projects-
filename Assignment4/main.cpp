
#include "ServiceCenter.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    if (argc != 2) return -1;
    ServiceCenter *center = new ServiceCenter(argv[1]);
    center->printResult();
}