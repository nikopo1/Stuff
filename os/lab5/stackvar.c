#include <stdio.h>

int *get_value(){
	int b;
	b = 2;
	return &b;
}
int main(void){
	int *a;
	int c = 3;
	a = get_value();
	printf("%d\n", c);
	printf("%d\n", *a);
	return 0;
}
