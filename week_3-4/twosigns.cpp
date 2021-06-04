#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

int main() {
    fstream file;
    double line;
    cout.precision(3);
    file.open("input.txt");
    if (file.is_open()) {
        do {
            file >> line;
            cout << std::fixed << line << endl;
        } while (!file.eof());
    }
    file.close();
    return 0;
}
