#include "common.h"


int main() {
	//Первоначальный размер массива на 64 контакта
	int size = 64;
	Contact* array = malloc(sizeof(Contact) * size);
	//Количество считанных элементов
	int ri = loadFILE("bkup.csv", array, 64);

	
	saveFILE("test.csv", array, ri);
	for (int i = 0; i < ri; i++)
		printUser(&array[i]);
	free(array);
	return 0;
}

