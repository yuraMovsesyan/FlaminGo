#include "header.h"

string resultLp = "";

int Lpcount = 0, Lpz[100], Lpy[100];

bool StartFileBoolLp = true;


void StartFileLp() {
	for (int i = 0; i < 100; i++) {
		Lpz[i] = 0;
		Lpy[i] = 0;
	}

	StartFileBoolLp = false;
}


string loopEndlp(int type, string* array, int size) {

	if (StartFileBoolLp)
		StartFileLp();

	print("loopEndlp", "inform");

	resultLp = "";
	if (type == 10) {

		if (Lpz[Lpcount] == 0) {
			Lpcount++;

			resultLp += "\nloopEndlp" + to_string(Lpcount) + to_string(Lpz[Lpcount]) + to_string(Lpy[Lpz[Lpcount]]) + ":\n";
			resultLp += ifElseEndif(7, array, size);

			Lpz[Lpcount]++;
		}
		else {
			Lpy[Lpz[Lpcount]]++;
			
			resultLp += "\nloopEndlp" + to_string(Lpcount) + to_string(Lpz[Lpcount]) + to_string(Lpy[Lpz[Lpcount]]) + ":\n";
			resultLp += ifElseEndif(7, array, size);

			Lpz[Lpcount]++;
			
		}



	}

	if (type == 11) {
		if (Lpz[Lpcount] != 0) {
			Lpz[Lpcount]--;
		}


		resultLp += "\njmp loopEndlp" + to_string(Lpcount) + to_string(Lpz[Lpcount]) + to_string(Lpy[Lpz[Lpcount]]) + "\n";
		resultLp += ifElseEndif(9, array, size);

		
	}

	print(resultLp, "code");

	return resultLp;
}