#pragma once
class RegisterFile{
    private:
        int registers[16];
    public:
        RegisterFile();
        int read(int index) const;
        void write(int index, int value);
        bool isValidIndex(int index)const;
        const int* getAll()const;
};