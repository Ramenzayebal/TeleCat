#include "common.h"


int main() {
	

	const char* fileName = "test.csv";
	Phonebook pb = { 0 };
	//Первоначальный размер массива на 64 контакта
	pb.capacity = 64;
	pb.contacts = malloc(sizeof(Contact)* pb.capacity);
	
	//Количество считанных элементов 
	loadFILE("bkup.csv", &pb);
	
	saveFILE(fileName, &pb);
	for (int i = 0; i < pb.count; i++)
		printUser(&pb.contacts[i]);
	free(pb.contacts);
	return 0;
}

