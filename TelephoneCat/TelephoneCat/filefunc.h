#pragma once
#include "common.h"
#include "phonebook.h" // Подключаем именно здесь, чтобы тип Phonebook был известен!

int loadFILE(const char* filename, Phonebook* pb);
int saveFILE(const char* filename, Phonebook* pb);
bool FILEexist(const char* filename);
void correct_string(char* str);
