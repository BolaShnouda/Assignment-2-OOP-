#include "RegisterFile.h"

RegisterFile::RegisterFile() {
    for(int i=0;i<16;i++){
        registers[i]=0;
    }
}

int RegisterFile::read(int index) const {
    if (!isValidIndex(index)) return 0;
    return registers[index];
}

void RegisterFile::write(int index, int value)  {
    if (!isValidIndex(index)) return;
    registers[index] = value & 0xFF;
}

bool RegisterFile::isValidIndex(int index) const {
    return index >= 0 && index < 16;
}

const int* RegisterFile::getAll() const {
    return registers;
}
