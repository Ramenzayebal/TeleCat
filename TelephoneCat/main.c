#include "common.h"
#include "phonebook.h"
#include "filefunc.h"

int main() {
	

	const char* fileName = "test.csv";
	Phonebook pb = { 0 };
	//Первоначальный размер массива на 64 контакта
	pb.capacity = 64;
	pb.contacts = malloc(sizeof(Contact)* pb.capacity);
	
	//Количество считанных элементов 
	loadFILE("bkup.csv", &pb);
	
	sortbyName(&pb);

	deleteUserbyindex(&pb, 0);

	saveFILE(fileName, &pb);

	for (int i = 0; i < pb.count; i++)
		printUser(&pb.contacts[i]);
	phonebook_free(&pb);
	return 0;
}

