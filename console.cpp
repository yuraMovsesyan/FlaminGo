#include "header.h"

enum ConsoleColor {
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

bool DeveloperMode = false;

void switchDeveloperMode(bool sDM) {
	DeveloperMode = sDM;
}

void loading(int a, int b) {
	if (!DeveloperMode) {
		system("cls");
		cout << to_string((a * 100) / b) << "%" << endl;
	}
}

void pause() {
	if (DeveloperMode)
		system("pause");
}

void print(string text, string status) {

	if (status == "inform")
		SetConsoleTextAttribute(hConsole, (WORD)((DarkGray << 4) | Yellow));

	if (status == "error")
		SetConsoleTextAttribute(hConsole, (WORD)((White << 4) | Red));

	if (status == "success")
		SetConsoleTextAttribute(hConsole, (WORD)((Green << 4) | White));

	if (status == "code")
		SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | White));

	if (status == "header")
		SetConsoleTextAttribute(hConsole, (WORD)((White << 4) | Blue));

	if (status == "update")
		SetConsoleTextAttribute(hConsole, (WORD)((Blue << 4) | White));

	if (DeveloperMode)
		cout << ">" << text << endl;
}

void printArray(string* arr, int size) {
	if (DeveloperMode) {
		cout << endl;
		for (int i = 0; i < size; i++) {
			cout << "[" << arr[i] << "]";
		}
	}
}