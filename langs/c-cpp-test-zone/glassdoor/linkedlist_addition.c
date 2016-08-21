#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

typedef struct list {
	struct list *next;
	int digit;
} list_t;

list_t* create_elem(int digit)
{
	list_t *elem = NULL;

	if(digit < 0)
		return NULL;

	elem = malloc(sizeof(list_t));
	if(elem == NULL) {
		perror("create_elem: malloc");
		return NULL;
	}

	elem->next = NULL;
	elem->digit = digit;

	return elem;
}

list_t* create_list(int number)
{
	list_t *res = NULL;
	list_t *elem = NULL;
	int digit, rest;

	rest = number;
	while(rest > 0) {
		digit = rest % 10;
		rest = rest / 10;

		elem = create_elem(digit);
		/* some error handling needed here, too lazy to write
		 * free functions */
		if(elem == NULL)
			break;

		elem->digit = digit;
		elem->next = res;
		res = elem;
	}

	return res;
}

list_t* add_lists(list_t *a, list_t *b)
{
	list_t *elem, *nextelem;
	int sum, overflow;

	if(a == NULL || b == NULL)
		return create_elem(0);

	elem = add_lists(a->next, b->next);

	sum = elem->digit + a->digit + b->digit;
	overflow = sum / 10;
	elem->digit = sum % 10;

	nextelem = create_elem(overflow);
	nextelem->next = elem;

	return nextelem;
}

list_t* addition(list_t *a, list_t *b)
{
	list_t *result = NULL;
	list_t *tmp = NULL;
	result = add_lists(a, b);

	if(result == NULL) {
		printf("Error in addition\n");
		return NULL;
	}

	if(result->digit == 0) {
		tmp = result;
		result = result->next;
		free(tmp);
	}

	return result;
}

void print_list(list_t *elem)
{
	while(elem) {
		printf("%d ", elem->digit);
		elem = elem->next;
	}
	printf("\n");
}

int main(int arvc, char *argv[])
{
	list_t *n1 = NULL;
	list_t *n2 = NULL;
	list_t *res = NULL;

	if(arvc != 3)
		return -1;

	n1 = create_list(atoi(argv[1]));
	n2 = create_list(atoi(argv[2]));
	res = addition(n1, n2);

	print_list(n1);
	print_list(n2);
	print_list(res);

	return 0;
}
