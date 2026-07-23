#pragma once
#include "common.h"

int loadFILE(const char*, Contact*, int);
int saveFILE(const char* , Contact* , int);
bool FILEexist(const char* );
void check_string(char* str);