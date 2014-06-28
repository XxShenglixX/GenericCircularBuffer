#include "Integer.h"
#include <stdio.h>

void copyInt(void *a,void *b)
{
	int  *address = (int *)a;
	int *value = (int *)b;

	*address = *value;
}