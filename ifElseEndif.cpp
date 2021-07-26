#include "header.h"

string arrCmdIf[3], resultIf = "";
int cmdIfId = 0;

string mathIf(string cmdIf, bool one);
int switchTypeIf(char a);

int idMetka = 0, elseOrEndif[100][100][100];
int Ifcount = 0, Ifz[100], Ify[100];
bool firstIf = true;

bool StartFileBool = true;

void Ifcode(string* array, int size);

void StartFile() {
	for (int i = 0; i < 100; i++) {
		Ifz[i] = 0;
		Ify[i] = 0;
	}

	for (int c = 0; c < 100; c++)
		for (int z = 0; z < 100; z++)
			for (int y = 0; y < 100; y++)
				elseOrEndif[c][z][y] = -1;
		
	StartFileBool = false;
}


string ifElseEndif(int type, string* array, int size) {

	//first run
	if (StartFileBool)
		StartFile();
	idMetka = 0;

	print("ifElseEndif", "inform");
	
	resultIf = "";
	//if
	if (type == 7) {
		idMetka = 0;

		if (Ifz[Ifcount] == 0) {
			Ifcount++;
			Ifcode(array, size);
			Ifz[Ifcount]++;
		}
		else {
			/*
			if (elseOrEndif[Ifcount][Ifz[Ifcount]][Ify[Ifz[Ifcount]]] == -1) {
				Ifcode(array, size);
				Ifz[Ifcount]++;
			}
			else {
			 */
				
				Ify[Ifz[Ifcount]]++;
				Ifcode(array, size);
				Ifz[Ifcount]++;
			//}
		}

		
		
	}

	//else
	if (type == 8) {
		if (Ifz[Ifcount] != 0) {
			Ifz[Ifcount]--;
			elseOrEndif[Ifcount][Ifz[Ifcount]][Ify[Ifz[Ifcount]]] = 0;
			resultIf += "\njmp _elseOrEndif" + to_string(Ifcount) + to_string(Ifz[Ifcount]) + to_string(Ify[Ifz[Ifcount]]) + "1";
			resultIf += "\n_elseOrEndif" + to_string(Ifcount) + to_string(Ifz[Ifcount]) + to_string(Ify[Ifz[Ifcount]]) + "0:\n";
			elseOrEndif[Ifcount][Ifz[Ifcount]][Ify[Ifz[Ifcount]]] = 1;
			Ifz[Ifcount]++;
		}
		else {
			elseOrEndif[Ifcount][Ifz[Ifcount]][Ify[Ifz[Ifcount]]] = 0;
			resultIf += "\njmp _elseOrEndif" + to_string(Ifcount) + to_string(Ifz[Ifcount]) + to_string(Ify[Ifz[Ifcount]]) + "1";
			resultIf += "\n_elseOrEndif" + to_string(Ifcount) + to_string(Ifz[Ifcount]) + to_string(Ify[Ifz[Ifcount]]) + "0:\n";
			elseOrEndif[Ifcount][Ifz[Ifcount]][Ify[Ifz[Ifcount]]] = 1;
		}
	}

	//enif
	if (type == 9) {
		if (Ifz[Ifcount] != 0) {
			Ifz[Ifcount]--;
		}

		if (elseOrEndif[Ifcount][Ifz[Ifcount]][Ify[Ifz[Ifcount]]] == -1) 
			elseOrEndif[Ifcount][Ifz[Ifcount]][Ify[Ifz[Ifcount]]] = 0;

		resultIf += "\n_elseOrEndif" + to_string(Ifcount) + to_string(Ifz[Ifcount]) + to_string(Ify[Ifz[Ifcount]]) + to_string(elseOrEndif[Ifcount][Ifz[Ifcount]][Ify[Ifz[Ifcount]]]) + ":\n";
		
		elseOrEndif[Ifcount][Ifz[Ifcount]][Ify[Ifz[Ifcount]]] = 0;
	}

	return resultIf;
}

string mathIf(string cmdIf, bool one) {
	int typeCmdIf = 0;
	cmdIfId = 0;
	
	

	string result = "";

	arrCmdIf[0] = "";
	arrCmdIf[1] = "";
	arrCmdIf[2] = "";
	
	for (int i = 0; i < cmdIf.size(); i++) {
		if (typeCmdIf != switchTypeIf(cmdIf[i])) {
			cmdIfId++;
			print("cmdIfId [" + to_string(cmdIfId) + "]", "update");
			if (cmdIfId == 3) break;
			typeCmdIf = switchTypeIf(cmdIf[i]);
		}
		arrCmdIf[cmdIfId] += cmdIf[i];
	}

	print("[" + arrCmdIf[0] + "]", "inform");
	if (checkVarOrMath(arrCmdIf[0]))
		result += varMoveEax(arrCmdIf[0]);
	else
		result += sortMath(arrCmdIf[0]);

	result += "\nmov [_aIf], eax\n";
	//print(result, "code");

	if (cmdIfId > 0) {
		print("[" + arrCmdIf[2] + "]", "inform");
		if (checkVarOrMath(arrCmdIf[2]))
			result += varMoveEax(arrCmdIf[2]);
		else
			result += sortMath(arrCmdIf[2]);

		result += "\nmov [_bIf], eax\n";

		//print(result, "code");
		print("[" + arrCmdIf[1] + "]", "inform");
		result += "\nmov eax, [_aIf]\nmov ebx, [_bIf]\ncmp eax, ebx\n";
		result += "\nmov edx, 1\n";

		if (arrCmdIf[1] == "==") result += "\nje ";
		if (arrCmdIf[1] == "!=") result += "\njne ";
		if (arrCmdIf[1] == "<") result += "\njl ";
		if (arrCmdIf[1] == "<=") result += "\njle ";
		if (arrCmdIf[1] == ">") result += "\njg ";
		if (arrCmdIf[1] == ">=") result += "\njge ";
	}
	else {
		result += "\nmov eax, [_aIf]\ncmp eax, 1\n";
		result += "\nmov edx, 1\n";
		result += "\njge ";
	}

	result += "_ifTrue" + to_string(Ifcount) + to_string(Ifz[Ifcount]) + to_string(Ify[Ifz[Ifcount]]) + to_string(idMetka) + "\n";
	if (one) {
		result += "\njmp _elseOrEndif" + to_string(Ifcount) + to_string(Ifz[Ifcount]) + to_string(Ify[Ifz[Ifcount]]) + "0\n";
		
	}
	result += "\nmov edx, 0\n_ifTrue" + to_string(Ifcount) + to_string(Ifz[Ifcount]) + to_string(Ify[Ifz[Ifcount]]) + to_string(idMetka) + ":\n";

	idMetka++;
	//print(result, "code");

	return result;
}

void Ifcode(string* Ifarray, int Ifsize) {
	if (Ifsize == 2) {
		resultIf += mathIf(Ifarray[1], true);

		print("result = \n" + resultIf, "code");
	}
	else {
		for (int i = 2; i < Ifsize; i += 2) {
			if (firstIf) {
				resultIf += mathIf(Ifarray[i - 1], false) + "mov ecx, edx\n";
				firstIf = false;
			}
			resultIf += mathIf(Ifarray[i + 1], false);
			if (Ifarray[i] == "&") resultIf += "\nand ecx, edx";
			if (Ifarray[i] == "|") {
				if (i + 2 < Ifsize && Ifarray[i + 2] == "&") {
					resultIf += "\nmov esi, ecx";

					resultIf += "\nmov ecx, edx";
					resultIf += mathIf(Ifarray[i + 3], false);
					resultIf += "\nand ecx, edx";
					resultIf += "\nor ecx, esi";

					i += 2;
				}
				else {

					resultIf += "\nor ecx, edx";
				}
			}

			print("result = \n" + resultIf, "code");
		}
		resultIf += "\ncmp ecx, 1\njne _elseOrEndif" + to_string(Ifcount) + to_string(Ifz[Ifcount]) + to_string(Ify[Ifz[Ifcount]]) + "0\n";
		print("result = \n" + resultIf, "code");
		firstIf = true;

	}
}

int switchTypeIf(char a) {
	switch (a)
	{
		case '<':
		case '>':
		case '=':
		case '!':	return 1;
	}
	return 0;
}