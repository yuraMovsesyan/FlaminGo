#include "header.h"

int switchType(char a);


bool pack = false;


bool famsEnfmStart = false;


string handling(string line) {
    
    int Type = 0, oldType = 0;

    
    string com = "";

    
    string result[100];
    int resultId = 0;

    for (int i = 0; i < line.size(); i++) {

        Type = switchType(line[i]);

        if (line[i] == '#') break;

        if ((line[i] == ' ' || line[i] == '\t') && !pack && systeamCMD(com) == 0) continue;
        
        if (line[i] == '"') {
            pack = !pack;

            if (com != "" && com[0] != '"') {
                result[resultId] = com;
                resultId++;
                oldType = Type;
                com = "";
            }
        }

        if (Type != 0 && !pack) {
            if (com != "") {
                result[resultId] = com;
                resultId++;
                oldType = Type;
                com = "";
            }

            if (line[i] == ',') {
                result[resultId] = ",";
                resultId++;
            }

            if (line[i] == '&') {
                result[resultId] = "&";
                resultId++;
            }

            if (line[i] == '|') {
                result[resultId] = "|";
                resultId++;
            }
        }
        else {
            com += line[i];
        }
    }

    if (com != "") {
        result[resultId] = com;
        resultId++;
        com = "";
    }
    

    //cout << "Kernel.cpp\n";
    print("Kernel.cpp", "inform");
    
    printArray(result, resultId);

    if (result[0] == "fasm") famsEnfmStart = true;

    if (!famsEnfmStart)
        sort(result, resultId);
    else
        if (result[0] != "fasm" && result[0] != "enfm")
            addFile("main.asm", "code/", line);

    if (result[0] == "enfm") famsEnfmStart = false;
    
    //cout << endl;
    return "";
}

/*
        0 - command
        1 - {, (
        2 - }, )
        3 - +, -, *, /
        4 - "
        5 - ,
        6 - пробел
        7 - #
        8 - \t
        9 - ;
*/
int switchType(char a) {
    switch (a)
    {

    case ',':   return 1;

    case ' ':   return 2;

    //case '#':   return 3;

    case '\t':   return 4;

    case '&':   return 6;

    case '|':   return 7;

    default:    return 0;
    }
}