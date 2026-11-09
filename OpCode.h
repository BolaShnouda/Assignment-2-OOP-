#ifndef OPCODE_H
#define OPCODE_H

#include <iostream>
using namespace std;

class OpCode {

private:

    Register& registers;
    Memory& memory;

    void executeLoad(int r, int address) {
        if (r < 0 || r > 15 || address < 0 || address > 255) {
            cout << "Invalid register or memory address!\n";
            return;
        }

        registers.setValue(r, memory.read(address));
    }

    void executeLoadImmediate(int r, int value) {
        if (r < 0 || r > 15) {
            cout << "Invalid register!\n";
            return;
        }

        registers.setValue(r, value);
    }

    void executeStore(int r, int address) {
        if (r < 0 || r > 15 || address < 0 || address > 255) {
            cout << "Invalid register or memory address!\n";
            return;
        }

        int value = registers.getValue(r);

        if (address == 0) {
            cout << "Output: " << value << endl;
        }
        else {
            memory.write(address, value);
        }
    }

    void executeMove(int r, int s) {
        if (r < 0 || r > 15 || s < 0 || s > 15) {
            cout << "Invalid register!\n";
            return;
        }

        registers.setValue(s, registers.getValue(r));
    }

    void executeAdd(int r, int s, int t) {
        if (r < 0 || r > 15 || s < 0 || s > 15 || t < 0 || t > 15) {
            cout << "Invalid register!\n";
            return;
        }

        int result = registers.getValue(s) + registers.getValue(t);

        registers.setValue(r, result & 0xFF);
    }

    void executeAddFloat(int r, int s, int t) {
        cout << "Floating-point format must be defined first!\n";
    }

    void executeJump(int r, int address, int& pc) {
        if (r < 0 || r > 15 || address < 0 || address > 255) {
            cout << "Invalid register or address!\n";
            return;
        }

        if (registers.getValue(r) == registers.getValue(0)) {
            pc = address;
        }
    }

    void executeHalt(bool& halted) {
        halted = true;
    }

public:

    OpCode(Register& reg, Memory& mem)
        : registers(reg), memory(mem) {}

    void execute(const Instruction& instruction, int& pc, bool& halted) {

        int opcode = instruction.getOpcode();

        int r = instruction.getR();
        int x = instruction.getX();
        int y = instruction.getY();

        switch (opcode) {

            case 0x1:
                executeLoad(r, x * 16 + y);
                break;

            case 0x2:
                executeLoadImmediate(r, x * 16 + y);
                break;

            case 0x3:
                executeStore(r, x * 16 + y);
                break;

            case 0x4:
                if (x != 0) {
                    cout << "Invalid MOVE instruction!\n";
                    break;
                }
                executeMove(y, r);
                break;

            case 0x5:
                executeAdd(r, x, y);
                break;

            case 0x6:
                executeAddFloat(r, x, y);
                break;

            case 0xB:
                executeJump(r, x * 16 + y, pc);
                break;

            case 0xC:
                if (r == 0 && x == 0 && y == 0) {
                    executeHalt(halted);
                }
                else {
                    cout << "Invalid HALT instruction!\n";
                }
                break;

            default:
                cout << "Invalid Opcode!\n";
        }
    }
};

#endif
