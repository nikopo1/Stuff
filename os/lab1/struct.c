#include <stdio.h>

typedef struct _tree_t {
	int idx;
	int data;
	struct _tree_t children[2];
} tree_t;

int main(void)
{
	printf("%d\n", sizeof(tree_t));
	return 0;
}
