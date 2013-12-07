#include "variable_include.h"

int function(int a)
{
	printf("%p\n", &my_variable);
	return a + my_variable;
}
