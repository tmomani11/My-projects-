#include "Menu.h"
using namespace std;

int main() {
    bool running = true;
    while(running){
        running = MainMenu();
    }
    cout << "Goodbye!" << endl;
  return 0;
}