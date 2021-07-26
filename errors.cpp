#include "header.h"

string Error[] = {
	"Не хватает ','",
	"Несуществующая команда",
	"Синтаксическая ошибка"
};

void error(int id) {
	print(Error[id], "error");
}