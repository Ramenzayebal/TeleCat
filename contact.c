#include "common.h"
#include "Contact.h"


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

