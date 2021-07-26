#include "header.h"

int switchType2(char a);


string CMD[100];
int CMDSize = 0;

int priority[100];
int priorityId = 0;


string sortMath(string cmd) {
	CMDSize = 0;

	priorityId = 0;

	print("math.cpp sortMath", "inform");

	string result = "", resultEnd = "";

	string comMath = "";

	int Type = 0, oldType = 0;

	bool firstCMD = !checkMathAssignment(cmd);
	bool firstEax = true;

	for (int i = 0; i < cmd.size(); i++) {
		Type = switchType2(cmd[i]);
		print("oldType = " + to_string(oldType), "error");
		print("Type = " + to_string(Type), "error");
		if (Type != oldType) {
			//if (comMath != "") {
				CMD[CMDSize] = comMath;
				print("CMD[" + to_string(CMDSize) + "] = " + CMD[CMDSize], "update");
				CMDSize++;
				comMath = "";

				oldType = Type;
				comMath += cmd[i];
			//}
		}
		else {
			comMath += cmd[i];
		}


	}

	print("CMDSize = " + to_string(CMDSize), "infrom");

	
	if (comMath != "") {
		CMD[CMDSize] = comMath;
		print("CMD[" + to_string(CMDSize) + "] = " + CMD[CMDSize], "update");
		CMDSize++;
		comMath = "";
	}

	cout << endl;
	for (int i = 0; i < CMDSize; i++) {
		cout << "[" << CMD[i] << "]";
	}
	cout << endl;

	if (CMD[1] == "++") {
		result = "mov eax, 1\nadd[a], eax\n";
		print("result: " + result, "success");
		print("resultEnd: " + resultEnd, "success");
		return result + resultEnd;
	}

	if (CMD[1] == "--") {
		result = "mov eax, 1\nsub[a], eax\n";
		print("result: " + result, "success");
		print("resultEnd: " + resultEnd, "success");
		return result + resultEnd;
	}

	//------------------------
	//priority
	/*
	0 - *
	1 - / | %
	2 - +
	3 - -
	*/
	//CMD[i]
	priorityId = 1;
	if (CMDSize >= 2) {
		if (CMD[1] == "=" || CMD[1] == "*=" || CMD[1] == "/=" || CMD[1] == "+=" || CMD[1] == "-=")
			priorityId += 2;
	}
	for (int j = 0; j < 4; j++) {
		for (int i = 1; i < CMDSize; i += 2) {
			if (CMD[i] == "*" && j == 0) {
				priority[priorityId] = i;
				print("priority: id = " + to_string(priorityId) + ", i = " + to_string(i) + ", *" ,"inform");
				priorityId += 2;
			}
			if (CMD[i] == "/" && j == 1) {
				priority[priorityId] = i;
				print("priority: id = " + to_string(priorityId) + ", i = " + to_string(i) + ", /", "inform");
				priorityId += 2;
			}
			if (CMD[i] == "+" && j == 2) {
				priority[priorityId] = i;
				print("priority: id = " + to_string(priorityId) + ", i = " + to_string(i) + ", +", "inform");
				priorityId += 2;
			}
			if (CMD[i] == "-" && j == 3) {
				priority[priorityId] = i;
				print("priority: id = " + to_string(priorityId) + ", i = " + to_string(i) + ", -", "inform");
				priorityId += 2;
			}
			if (CMD[i] == "%" && j == 1) {
				priority[priorityId] = i;
				print("priority: id = " + to_string(priorityId) + ", i = " + to_string(i) + ", -", "inform");
				priorityId += 2;
			}
		}
	}

	//------------------------
	
	for (int i = 1; i < CMDSize; i+=2) {
		if (!firstCMD) {
			print("firstCMD CMD[" + to_string(i) + "] = " + CMD[i - 1], "inform");
			if (CMD[i] == "=") {
				resultEnd += "\nmov [" + CMD[i - 1] + "], eax";

				VarMarkFunction(CMD[i - 1]);

			}

			if (CMD[i] == "+=") resultEnd += "\nadd [" + CMD[i - 1] + "], eax";
			if (CMD[i] == "-=") resultEnd += "\nsub [" + CMD[i - 1] + "], eax";
			if (CMD[i] == "*=") resultEnd += "\nimul [" + CMD[i - 1] + "], eax";
			if (CMD[i] == "/=") resultEnd += "\nmov edx, 0\nmov ebx, eax\nmov eax, [" + CMD[i - 1] + "]\ndiv ebx\nmov [" + CMD[i - 1] + "], eax";
			if (CMD[i] == "%=") resultEnd += "\nmov edx, 0\nmov ebx, eax\nmov eax, [" + CMD[i - 1] + "]\ncdq\ndiv ebx\nmov eax, edx\nmov [" + CMD[i - 1] + "], eax";
			//if (CMD[i] == "++") result += "\ninc " + CMD[i - 1];
			//if (CMD[i] == "--") result += "\ndec " + CMD[i - 1];

			//if (cmd[i] != "=") error(2);
			
			firstCMD = true;
		}
		else {
			print("CMD[" + to_string(i) + "] = " + CMD[i], "inform");

			//result += "\nmov eax, " + CMD[i - 1];
			if (firstEax) {
				if (CallFindVar(CMD[priority[i] - 1]) == -1)
					result += "\nmov eax, " + CMD[i - 1];
				else
					result += "\nmov eax, [" + CMD[i - 1] + "]";
				firstEax = false;
			}
			
			//result += "\nmov ebx, [" + CMD[i + 1] + "]";
			if (CallFindVar(CMD[priority[i] + 1]) == -1)
				result += "\nmov ebx, " + CMD[priority[i] + 1];
			else
				result += "\nmov ebx, [" + CMD[priority[i] + 1] + "]";

			if (CMD[priority[i]] == "+") result += "\nadd eax, ebx";
			if (CMD[priority[i]] == "-") result += "\nsub eax, ebx";
			if (CMD[priority[i]] == "*") result += "\nimul eax, ebx";
			if (CMD[priority[i]] == "/") result += "\nmov edx, 0\ndiv ebx";
			if (CMD[priority[i]] == "%") result += "\nmov edx, 0\ncdq\ndiv ebx\nmov eax, edx";//\nmov ax, ah
			/*if (CMD[priority[i]] != "+" && CMD[priority[i]] != "-" && CMD[priority[i]] != "*" && CMD[priority[i]] != "/")
				error(2);*/

		}
	}

	if (CMDSize == 3 && checkMathAssignment(cmd)) {
		if (CallFindVar(CMD[2]) == -1)
			result += "\nmov eax, " + CMD[2] + "";
		else
			result += "\nmov eax, [" + CMD[2] + "]";
	}



	//&& cmd[cmd.size() - 1] == ':'
	if (CMDSize == 1) {
		if (cmd[cmd.size() - 1] == ':') {
			VarMarkFunction(cmd);
		}
		else{
			addFile("main.asm", "code/", "\ncall _" + cmd);
			print("Add call mark : " + cmd, "inform");
		}
	}
	
	print("result: " + result, "success");
	print("resultEnd: " + resultEnd, "success");
	return result + resultEnd;
}

/*
a = b + 1

mov eax, b
mov ebx, 1
add eax, ebx

mov a, eax

*/

int switchType2(char a) {
	switch (a)
	{
	case '{':
	case '(':   return 1;

	case '}':
	case ')':   return 2;

	case '=':
	case '%':
	case '+':
	case '-':
	case '*':
	case '/':   return 3;

	case '"':   return 4;

	case ',':   return 5;

	case ' ':   return 6;

	case '#':   return 7;

	case '\t':   return 8;

	case ';':   return 9;

	default:    return 0;
	}
}

string varMoveEax(string cmd) {
	if (CallFindVar(cmd) == -1) {

		if (cmd == "true")
			return "\nmov eax, 1";

		if (cmd == "false")
			return "\nmov eax, 0";

		return "\nmov eax, " + cmd;
	}
	else {
		return "\nmov eax, [" + cmd + "]";
	}

	return "error";
}