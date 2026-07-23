#include "common.h"
#include "phonebook.h"
#include "filefunc.h"

#define BUFFER 256


//Функция читает файл, считывает всё в массив контактов и
//возвращает количество считанных элементов
int loadFILE(const char* filename, Phonebook* pb)
{
	if (!FILEexist(filename))
	{
		printf("Файл не существует");
		return ERROR;
	}

	FILE* fp = fopen(filename, "r");
	char buffer[BUFFER];
	
	if (fp == NULL)
	{
		perror("Ошибка открытия файла");
		return ERROR;
	}
	int readitems = 0;
	int count = 0;
	int index = 0;
	while (fgets(buffer, BUFFER, fp) && index < pb->capacity)
	{
		count = 0;
		char* value = strtok(buffer, "; \n");
		while (value) 
		{
			switch (count)
			{
			case 0: 
				strncpy(pb->contacts[index].number, value, sizeof(pb->contacts[index].number) - 1);
				pb->contacts[index].number[sizeof(pb->contacts[index].number) - 1] = '\0';
				correct_string(pb->contacts[index].number);
				break;
			case 1: 
				strncpy(pb->contacts[index].name, value, sizeof(pb->contacts[index].name) - 1);
				pb->contacts[index].name[sizeof(pb->contacts[index].name) - 1] = '\0';
				correct_string(pb->contacts[index].name);
				break;
			case 2: 
				strncpy(pb->contacts[index].last_name, value, sizeof(pb->contacts[index].last_name) - 1);
				pb->contacts[index].last_name[sizeof(pb->contacts[index].last_name) - 1] = '\0';
				correct_string(pb->contacts[index].last_name);
				break;
			case 3: 
				strncpy(pb->contacts[index].surname, value, sizeof(pb->contacts[index].surname) - 1);
				pb->contacts[index].surname[sizeof(pb->contacts[index].surname) - 1] = '\0';
				correct_string(pb->contacts[index].surname);
				break;
			}
			count++;
			value = strtok(NULL, "; \n");
		}
		index++;
		readitems++;
	}
	fclose(fp);
	pb->count = readitems;
	return readitems;
}

//Сохраняет в файл данные из озу
int saveFILE(const char* filename, Phonebook* pb)
{
	FILE* fp = fopen(filename, "w");
	if (fp == NULL)
	{
		perror("Ошибка открытия файла");
		return ERROR;
	}
	for (int i = 0; i < pb->count; i++)
	{
		loadUser(fp, &pb->contacts[i]);
	}
	fclose(fp);
	return 0;
}

//Проверка файла на существование
bool FILEexist(const char* filename)
{
	FILE* fp = fopen(filename, "r");
	if (fp != NULL)
	{
		fclose(fp);
		return true;
	}
	return false;
}


//Корректор строки
void correct_string(char* str)
{
	if (str == NULL) return;
	int i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ';')
			str[i] = ' ';
		else if (str[i] == '\n' || str[i] == '\r')
		{
			str[i] = '\0';
			break;
		}
		i++;
	}
}
