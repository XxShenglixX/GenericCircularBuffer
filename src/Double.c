#include "Double.h"

void copyDouble(void *a,void *b)
{
	double  *address = (double *)a;
	double *value = (double *)b;
	
	*address = *value;
}