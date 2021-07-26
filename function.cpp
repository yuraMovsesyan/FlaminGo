#include "header.h"



bool checkNumber(char a) {
	switch (a)
	{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':	return true;
	}

	return false;
}


bool checkVarMarkFunction(string* array, int id, string text) {
	for (int i = 0; i < id; i++) {
		print("Check var: " + array[i], "inform");
		if (array[i] == text) {
			return false;
		}
	}
	return true;
}

int systeamCMD(string cmd) {

	print("systeamCMD - [" + cmd + ']', "inform");

	if (cmd == "write") return 1;
	if (cmd == "writeline") return 2;

	if (cmd == "read") return 3;
	if (cmd == "readline") return 4;

	if (cmd == "scan") return 5;
	if (cmd == "scanline") return 6;

	if (cmd == "if") return 7;
	if (cmd == "else") return 8;
	if (cmd == "endif" || cmd == "enif") return 9;
	//if (cmd == "elif") return 10;

	if (cmd == "loop") return 10;
	if (cmd == "enlp" || cmd == "endlp") return 11;


	return 0;
}

bool sesteamCmdForWindows(string cmd) {
	if (cmd == "endl")	return true;
	if (cmd == "true")	return true;
	if (cmd == "false")	return true;

	return false;
}

//var - true; Math - false
bool checkVarOrMath(string cmd) {
	for (int i = 0; i < cmd.size(); i++) {
		switch (cmd[i])
		{
			case '%':
			case '+':
			case '-':
			case '*':
			case '/':
			case '=':	return false;
			case '"':	return true;
		}
	}

	return true;
}


bool checkMathAssignment(string cmd) {
	for (int i = 0; i < cmd.size(); i++) {
		if (cmd[i] == '=')	return true;
	}

	return false;
}


int findVar(string* array, int id, string text) {
	for (int i = 0; i < id; i++) {
		print("Find var: " + array[i], "inform");
		if (array[i] == text) {
			return i;
		}
	}
	return -1;
}