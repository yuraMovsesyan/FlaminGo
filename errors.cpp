#include "header.h"

string Error[] = {
	"�� ������� ','",
	"�������������� �������",
	"�������������� ������"
};

void error(int id) {
	print(Error[id], "error");
}