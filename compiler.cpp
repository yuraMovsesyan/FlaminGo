#include "header.h"

void addCMD(string cmd);

int Type = 0;

string variable[100];
int variableId = 0;

bool variableType[100];
int variableTypeId = 0;

string mark[100];
int markId = 0;


bool firstCMD = true;	


void sort(string *cmd, int size) {

	print("Compiler.cpp sort", "inform");

	for (int i = 0; i < size; i++) {
		
		if (firstCMD) {
			Type = systeamCMD(cmd[i]);
			firstCMD = false;
			print("Type = " + to_string(Type), "inform");

			if (Type == 0) 
				addFile("main.asm", "code/", sortMath(cmd[i]));
			if (Type == 7 || Type == 8 || Type == 9) {
				addFile("main.asm", "code/", ifElseEndif(Type, cmd, size));
				break;
			}

			if (Type == 10 || Type == 11) {
				addFile("main.asm", "code/", loopEndlp(Type, cmd, size));
				break;
			}
				
		}
		else {
			if (cmd[i][0] != ',') {
				addCMD(cmd[i]);
			}
		}
	}

	if (cmd[size - 1] != "," && size > 0)
		firstCMD = true;
	
}

void addCMD(string cmd){
	
	print("addCMD", "inform");

	string text = "";
	
	if (checkVarOrMath(cmd)){
		text += "\n";
		switch (Type)
		{
			case 1:
			case 2:
				if (cmd[0] == '"') {
					text += "stdcall StringCopy," + cmd + ", write, " + to_string(cmd.size() - 1) + "\npush write\ncall[printf]\n";
					text += "stdcall StringCopy, '', write, " + to_string(cmd.size() - 1);
				}
				else {
					//if (variableType[])
					text += "push ";
					variableTypeId = findVar(variable, variableId, cmd);
					if (variableTypeId != -1) {
						if (variableType[variableTypeId])
							text += "["+ cmd + "]\npush formatNum";
						else
							text += cmd + "\npush formatStr";
					}
					else {
						text += cmd + "\npush formatStr";
					}
					text += "\ncall[printf]";
				}
				break;
			case 3: text += "push " + cmd + "\ncall[getch]"; break;
			case 4: text += "push " + cmd + "\npush formatStr\ncall[scanf]"; break;

			case 5: text += "push " + cmd + "\npush formatNum\ncall[scanf]"; break;
			case 6: text += "push " + cmd + "\npush formatNum\ncall[scanf]"; break;
		}
	}
	else {
		text = sortMath(cmd);
		switch (Type)
		{
			case 1:
			case 2:
				text += "\npush eax\npush formatNum\ncall[printf]";
			break;
		}
	}
	
	switch (Type) {
		case 2: text += "\npush endl\ncall[printf]"; break;
	}
	
	
	print("Code { \n" + text + "\n}", "code");
	addFile("main.asm", "code/", text);
	
	VarMarkFunction(cmd);
}

void VarMarkFunction(string cmd) {
	string text;
	if (cmd[0] != '_' && cmd[cmd.size() - 1] != ':' && cmd[0] != '"' && !sesteamCmdForWindows(cmd) && checkVarOrMath(cmd)) {
		if (checkVarMarkFunction(variable, variableId, cmd)) {
			text = cmd + " rd 10\n";
			addFile("header.asm", "code/", text);
			print("Add var : " + cmd, "success");


			variable[variableId] = cmd;
			variableType[variableId] = false;
			switch (Type)
			{
				case 0:
				case 5:
				case 6:
				variableType[variableId] = true;
			}
			if (variableType[variableId])
				print("Add Type : true", "update");
			else
				print("Add Type : false", "update");
			variableId++;

		}
	}
	else {
		if (cmd[cmd.size() - 1] == ':') {
			text = "\n_" + cmd;
			cmd[cmd.size() - 1] = '\0';
			addFile("main.asm", "code/", text);
			print("Add mark : " + cmd, "success");
			mark[markId] = cmd;
			markId++;
		}
	}
}

int CallFindVar(string cmd) {
	return findVar(variable, variableId, cmd);
}
