#include "header.h"

void saveFile(string name, string location, string text) {
    ofstream file(location + name);

    file << text;

    file.close();
}

ofstream out; 
void addFile(string name, string location, string text) {
    out.open(location + name, ios::in);
    out.seekp(0, ios::end);
    out << text;
    out << endl; 
    out.close(); 
}