#include "DataBase.h"
using namespace std;

int main() {
    bool running = true;
    DataBase db;
    while(running){
        running = db.MainMenu();
    }
    cout << "Goodbye!" << endl;
    return 0;
}