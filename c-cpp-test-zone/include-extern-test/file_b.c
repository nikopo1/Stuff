#include "variable_include.h"

#include <stdio.h>

int function(int);

static int function2(int b)
{
	printf("%p\n", &my_variable);
	return b + my_variable;
}

int main(void)
{
	printf("%d\n", function(2) + function2(3));
	return 0;
}
