#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

#if defined(UNICODE)
#define _tstring wstring
#else
#define _tstring string
#endif

using namespace std;

void saveFile(string name, string location, string text);
void addFile(string name, string location, string text);
void print(string text, string status);
void printArray(string* arr, int size);
void build(string map, string name);
void switchDeveloperMode(bool sDM);
void sort(string* cmd, int size);
void VarMarkFunction(string cmd);
void loading(int a, int b);
void error(int id);
void pause();
int findVar(string* array, int id, string text);
int CallFindVar(string cmd);
int systeamCMD(string cmd);
bool checkVarMarkFunction(string* array, int id, string text);
bool sesteamCmdForWindows(string cmd);
bool checkMathAssignment(string cmd);
bool checkVarOrMath(string cmd);
bool checkNumber(char a);
string ifElseEndif(int type, string* array, int size);
string loopEndlp(int type, string* array, int size);
string varMoveEax(string cmd);
string sortMath(string cmd);
string handling(string line);