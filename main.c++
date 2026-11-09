#include <iostream>
#include "RegisterFile.h"
using namespace std;
int main() {
    RegisterFile rf;
    rf.write(3, 0x1FF);
    cout << rf.read(3) << "\n";           
    cout << rf.read(15) << "\n";          
    cout << rf.isValidIndex(16) << "\n";  
}