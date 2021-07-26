#include "header.h"

//string map = "code\\";

void build(string map, string name) {
	saveFile(name + ".asm", map, "");

	//header
	ifstream file("code\\pattern\\header.asm");
	string line;

	while (file.peek() != EOF) {


		getline(file, line);

		addFile(name + ".asm", map, line);
	}
	file.close();

	file.open("code\\header.asm");

	while (file.peek() != EOF) {


		getline(file, line);

		addFile(name + ".asm", map, line);
	}
	file.close();

	//main

	file.open("code\\pattern\\main.asm");

	while (file.peek() != EOF) {


		getline(file, line);

		addFile(name + ".asm", map, line);
	}
	file.close();

	file.open("code\\main.asm");

	while (file.peek() != EOF) {


		getline(file, line);

		addFile(name + ".asm", map, line);
	}
	file.close();

	//footer

	file.open("code\\pattern/footer.asm");

	while (file.peek() != EOF) {


		getline(file, line);

		addFile(name + ".asm", map, line);
	}
	file.close();


	string cmdFasm = "\".\\fasm\\fasm.exe\" \"" + map + name + ".asm" + "\"";
	cout << cmdFasm << endl;


	LPCSTR pcstr;
	string str = cmdFasm;
	pcstr = str.c_str();

	WinExec(pcstr, SW_HIDE);
}
