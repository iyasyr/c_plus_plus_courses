#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

int main() {
    fstream file;
    string line;
    file.open("input.txt");
    if (file.is_open()) {
        while (getline(file, line))
            cout << line << endl;
    }
    file.close();
    return 0;
}