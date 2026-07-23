#pragma once

//Поля контакта
typedef struct {
	char number[16];
	char name[64];
	char last_name[64];
	char surname[64];
} Contact;

//Поля каталога
typedef struct {
	Contact* contacts;
	int count;
	int capacity;
} Phonebook;


void printUser(Contact* );
int loadUser(FILE*, Contact* );
void copyUser(const Contact* source, Contact* dest);
void addUser(Phonebook* pb, const Contact* new_contact);
void deleteUserbyindex(Phonebook* pb, int index);