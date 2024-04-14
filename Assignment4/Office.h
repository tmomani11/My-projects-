
#ifndef OFFICE_H
#define OFFICE_H

#include "Window.h"
#include "ListQueue.h"
#include <cstdlib>
using namespace std;

class Office{
    public:
        Office();
        Office(int numWindows);
        virtual ~Office();
        void addCustomer(Customer* c1, int numWindow);
        int shortestLine();
        void nextCustomer(int numWindow);
        int queueSizeOffice(int numWindow);
        
    protected:
        Window* manager;
        int nW;
        
};

#endif