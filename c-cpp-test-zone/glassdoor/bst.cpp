#include <stack>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>

typedef struct bst {
	int info;
	struct bst *left;
	struct bst *right;
	struct bst *parent;
} bst_t;

bst_t* create_node(int value)
{
	bst_t *ret = NULL;

	ret = (bst_t*) malloc(sizeof(bst_t));
	if(ret == NULL) {
		perror("create_node: out of memory");
		return NULL;
	}

	ret->info = value;
	ret->left = NULL;
	ret->right = NULL;
	ret->parent = NULL;

	return ret;
}

void insert_node(bst_t *root, int value)
{
	while(root != NULL) {
		if(value <= root->info) {
			if(root->left == NULL) {
				root->left = create_node(value);
				root->left->parent = root;
				break;
			} else {
				root = root->left;
			}
		} else {
			if(root->right == NULL) {
				root->right = create_node(value);
				root->right->parent = root;
				break;
			} else {
				root = root->right;
			}
		}
	}
}

bst_t* create_bst(int array[], int size)
{
	int i;
	bst_t *ret = NULL;

	if(size <= 0) {
		perror("create_bst: 0 size");
		return NULL;
	}

	ret = create_node(array[0]);

	for(i = 1; i < size; i++) {
		insert_node(ret, array[i]);
	}

	return ret;
}

bst_t* find_value(bst_t *root, int value)
{
	bst_t *node = NULL;

	if(root == NULL)
		return NULL;

	if(root->info == value)
		return root;

	node = find_value(root->left, value);
	if(node)
		return node;

	node = find_value(root->right, value);
	if(node)
		return node;

	return NULL;
}

bst_t* replace_value(bst_t *root, int value, int replacement)
{
	bst_t *node = find_value(root, value);
	if(!node)
		return NULL;

	node->info = replacement;
	return node;
}

bst_t* is_bst(bst_t *root, int min, int max)
{
	bst_t *node;

	if(root == NULL)
		return NULL;

	/* check current node */
	if(root->info < min || root->info > max)
		return root;

	/* check left subtree */
	node = is_bst(root->left, min, root->info);
	if(node)
		return node;

	/* check right subtree */
	node = is_bst(root->right, root->info, max);
	if(node)
		return node;

	return NULL;
}

bst_t* is_bst_iterative(bst_t *root)
{
	bst_t *p = NULL;
	std::stack < bst_t* > s;
	std::stack < std::pair<int, int> > limits;
	std::pair <int, int> interval;
	int min = INT_MIN;
	int max = INT_MAX;

	s.push(root);
	limits.push(std::pair<int, int>(min, max));

	while(!s.empty()) {
		/* grab next node */
		p = s.top();
		s.pop();

		interval = limits.top();
		limits.pop();

		/* check current node */
		if(p->info < interval.first || p->info > interval.second)
			return p;

		/* add descendents to stack */
		if(p->left) {
			s.push(p->left);
			limits.push(std::pair<int, int>(interval.first, p->info));
		}
		if(p->right) {
			s.push(p->right);
			limits.push(std::pair<int, int>(p->info, interval.second));
		}
	}

	return NULL;
}

bst_t* find_right_sibling(bst_t *root, bst_t *node)
{
	bst_t *p = root;
	bst_t *predecessor = NULL;

	if(node == NULL) {
		perror("find_right_sibling: node is null");
		return NULL;
	}

	if(root == node) {
		perror("find_right_sibling: node is root");
		return NULL;
	}

	while(p) {
		if(p->left == node)
			return p->right;

		/* explore left subtree */
		if(p->left != NULL && p->left != predecessor && (p->right == NULL || (p->right != NULL && p->right != predecessor))) {
			p = p->left;
			continue;
		}

		/* explore right subtree */
		if(p->right != NULL && p->right != predecessor) {
			p = p->right;
			continue;
		}

		/* check if both subtrees have been explored */
		predecessor = p;
		p = p->parent;
	}

	return NULL;
}

void print_bst(bst_t *root)
{
	if(root == NULL)
		return;

	print_bst(root->left);
	printf("%d ", root->info);
	print_bst(root->right);
}

void testbed_is_bst(void)
{
	bst_t *root = NULL;
	bst_t *node = NULL;
	bst_t *sibling = NULL;
	int n = 6;
	int m[][10] = {
		{0},
		{0},
		{0, 0},
		{0, 0, 0, 0},
		{6, 2, -4, -2, 5, 12, 8, 7, 9, 15},
		{6, 2, -4, -2, 5, 12, 8, 7, 9, 15}
	};
	int v[][2] = {
		{0, 0},
		{0, 1},
		{0, 2},
		{0, 3},
		{8, 20},
		{5, 20}
	};
	int size[] = {0, 1, 2, 4, 10, 10};

	for(int i = 0; i < n; i++) {
		root = NULL;

		root = create_bst(m[i], size[i]);
		if(root == NULL)
			continue;

		print_bst(root);
		printf("\n\n");

		printf("Testing find_right_sibling\n");
		for(int j = 0; j < size[i]; j++) {
			node = find_value(root, m[i][j]);

			sibling = find_right_sibling(root, node);
			if(sibling == NULL)
				printf("Sibling not found\n");
			else
				printf("Sibling of %d is %d\n", node->info, sibling->info);
		}

		replace_value(root, v[i][0], v[i][1]);

		print_bst(root);
		printf("\n\n");

		printf("Testing is_bst\n");
		node = is_bst(root, INT_MIN, INT_MAX);
		printf("Correct binary tree? %4s (%d)\n", (node == NULL? "Yes." : "No."), (node == NULL? 0 : node->info));
		node = is_bst_iterative(root);
		printf("Correct binary tree? %4s (%d) (iterative)\n", (node == NULL? "Yes." : "No."), (node == NULL? 0 : node->info));
	}
}

int main(void)
{
	testbed_is_bst();
	return 0;
}
