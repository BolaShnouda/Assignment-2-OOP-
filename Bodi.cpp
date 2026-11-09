#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace  std;
class Main_Memory {
private:
    vector<string>Register[16];
    vector<string>cells[256];
    fstream LoadedFile;
 public:
    void instructionFile() {
        string str;
        string str1;
        cout<<"Load your InstructionFileName.txt\n";
        cin>>str;
        LoadedFile.open(str,ios::in);
        if (LoadedFile.is_open()) {
            int i = 0;
            while (getline(LoadedFile,str1)) {
                string c1 = str1.substr(0,2);
                string c2 = str1.substr((2 ,2));
                cells[i].push_back(c1);
                cells[i+1].push_back(c2);
                i += 2;
            }
            LoadedFile.close();
        }
    }
      void RegToMemo(string s1,string s2) {
        int c1 = stoi(s1,nullptr,16);
        int c2 = stoi(s2);
        cells[c1] = Register[c2];
    }
      void MemoToReg(string s1,string s2) {
        int c1 = stoi(s1,nullptr,16);
        int c2 = stoi(s2);
       Register[c2] = cells[c1];
    }
};

int main() {

}
