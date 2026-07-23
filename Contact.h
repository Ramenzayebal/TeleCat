#pragma once

typedef struct {
	char number[16];
	char name[64];
	char last_name[64];
	char surname[64];
} Contact;

void printUser(Contact* );
int scanUser(FILE*, Contact* );