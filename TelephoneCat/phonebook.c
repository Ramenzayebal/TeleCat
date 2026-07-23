#include "common.h"
#include "phonebook.h"


void printUser(Contact* user)
{
	printf("%s %s %s %s\n", user->number, user->name, user->last_name, user->surname);
}

int loadUser(FILE* fp, Contact* user)
{
	if(fprintf(fp, "%s;%s;%s;%s\n", user->number, user->name, user->last_name, user->surname) == ERROR) 
		return 1;
	return 0;
}

void copyUser(const Contact* source, Contact* dest)
{
	if (source == NULL) return;
	strncpy(dest->number, source->number, sizeof(dest->number) - 1);
	dest->number[sizeof(dest->number) - 1] = '\0';

	strncpy(dest->name, source->name, sizeof(dest->name) - 1);
	dest->name[sizeof(dest->name) - 1] = '\0';

	strncpy(dest->last_name, source->last_name, sizeof(dest->last_name) - 1);
	dest->last_name[sizeof(dest->last_name) - 1] = '\0';

	strncpy(dest->surname, source->surname, sizeof(dest->surname) - 1);
	dest->surname[sizeof(dest->surname) - 1] = '\0';
}

void renewMemory(Phonebook* pb)
{
	Contact* tmp = realloc(pb->contacts, pb->capacity * sizeof(Contact));
	if (tmp == NULL)
	{
		perror("Ошибка перевыделения памяти");
		return;
	}
	pb->contacts = tmp;
}

void addUser(Phonebook* pb, const Contact* new_contact)
{

	if (pb->count < pb->capacity)
	{
		copyUser(new_contact, &(pb->contacts[pb->count]));
		pb->count++;
	}
	else renewMemory(pb);
}

void deleteUserbyindex(Phonebook* pb, int index)
{
	if (index > pb->count || index < 0)
	{
		printf("Неверный индекс");
		return;
	}
	Contact tmp = { 0 };
	for (size_t i = index; i < pb->count - 1; i++)
	{
		copyUser(&pb->contacts[i + 1], &pb->contacts[i]);
	}
	copyUser(&tmp, &pb->contacts[pb->count]);
	pb->count--;
}

void phonebook_free(Phonebook* pb)
{
	if (pb->contacts != NULL)
	{
		free(pb->contacts);
		pb->contacts = NULL;
	}
	pb->capacity = 0;
	pb->count = 0;
}

int compareStrbyName(const void* a, const void* b)
{
	const Contact* contact1 = (const Contact*) a;
	const Contact* contact2 = (const Contact*) b;
	return strcmp(contact1->name, contact2->name);
}

void sortbyName(Phonebook* pb)
{
	qsort(pb->contacts, pb->count, sizeof(Contact), compareStrbyName);
}