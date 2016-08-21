#include <stdio.h>
#include <stdlib.h>

typedef struct list {
	int info;
	struct list *next;
} list_t;

int remove_duplicates(list_t *list)
{
	int count = 0;
	list_t *p, *del;

	while(list) {
		p = list;
		while(p->next) {
			if(p->next->info == list->info) {
				count++;
				del = p->next;
				p->next = p->next->next;
				free(del);
			} else {
				p = p->next;
			}
		}
		list = list->next;
	}
	
	return count;
}

list_t* make_list(int* array, int size)
{
	list_t *result, *p, *prev;
	int i;

	result = NULL;
	for(i = 0; i < size; i++) {
		p = malloc(sizeof(list_t));
		if(p == NULL) {
			perror("malloc");
			exit(-1);
		}
		p->next = NULL;

		if(result == NULL)
			result = p;

		p->info = array[i];
		prev->next = p;
		prev = p;
	}
	return result;
}

void print_list(list_t *list)
{
	while(list) {
		printf("%d", list->info);
		if(list->next)
			printf(", ");
		list = list->next;
	}
	printf("\n");
}

int main(void)
{
	list_t *list;
	int a[] = { 1, 2, 1, 3, 3, 5, 8, 5 };
	int count;

	list = make_list(a, 8);
	print_list(list);
	
	count = remove_duplicates(list);
	printf("Deleted %d list elements\n", count);
	print_list(list);

	return 0;
}
