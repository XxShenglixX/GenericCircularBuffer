#include "Integer.h"
#include <stdio.h>

void copyInt(void *a,void *b)
{
	int  *head = (int *)a;
	int *value = (int *)b;

	*head = *value;
}