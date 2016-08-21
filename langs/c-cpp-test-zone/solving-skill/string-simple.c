#include <stdio.h>
#include <string.h>

void reverse(char *s)
{
	char *p, aux;
	if(s == NULL)
		return;

	p = s;
	while(*p) {
		p++;
	}
	p--;

	while(s < p) {
		aux = *p;
		*p = *s;
		*s = aux;
		s++;
		p--;
	}
}

int main(void)
{
	char *str1, *str2;

	str1 = strdup("1234567890");
	if(str1 == NULL)
		return -1;

	str2 = strdup("1234567");
	if(str2 == NULL)
		return -1;

	printf("str1:\n\t%s\n", str1);
	reverse(str1);
	printf("\t%s\n", str1);

	printf("str2:\n\t%s\n", str2);
	reverse(str2);
	printf("\t%s\n", str2);

	return 0;
}
