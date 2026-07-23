#include "common.h"
#include "filefunc.h"
#define BUFFER 230


//Функция читает файл, считывает всё в массив контактов и
//возвращает количество считанных элементов
int loadFILE(const char* filename, Contact* array, int size)
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
	while (fgets(buffer, BUFFER, fp) && index < size)
	{
		count = 0;
		char* value = strtok(buffer, "; \n");
		while (value) 
		{
			switch (count)
			{
			case 0: 
				strncpy(array[index].number, value, sizeof(array[index].number) - 1);
				array[index].number[sizeof(array[index].number) - 1] = '\0';
				break;
			case 1: 
				strncpy(array[index].name, value, sizeof(array[index].name) - 1);
				array[index].name[sizeof(array[index].name) - 1] = '\0';
				
				break;
			case 2: 
				strncpy(array[index].last_name, value, sizeof(array[index].last_name) - 1);
				array[index].last_name[sizeof(array[index].last_name) - 1] = '\0';
				
				break;
			case 3: 
				strncpy(array[index].surname, value, sizeof(array[index].surname) - 1);
				array[index].surname[sizeof(array[index].surname) - 1] = '\0';
				
				break;
			}
			count++;
			//printf("%s ", value);
			value = strtok(NULL, "; \n");
		}
		index++;
		readitems++;
		//printf("\n");
	}
	fclose(fp);
	return readitems;
}

//Сохраняет в файл данные из озу
int saveFILE(const char* filename, Contact* array, int size)
{
	FILE* fp = fopen(filename, "w");
	char buffer[BUFFER];
	if (fp == NULL)
	{
		perror("Ошибка открытия файла");
		return ERROR;
	}
	for (int i = 0; i < size; i++)
	{
		loadUser(fp, &array[i]);
	}
	fclose(fp);
	return 0;
}

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


//
void check_string(char* str)
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



