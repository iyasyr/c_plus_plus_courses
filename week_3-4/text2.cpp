#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

int main(){
    fstream file, fout;
    string line;
    fout.open("output.txt", ios::out);
    file.open("input.txt", ios::in);
    if (file.is_open()) {
        while (getline(file, line))
            fout << line << endl;
    }
    file.close();
    fout.close();
    return 0;
}