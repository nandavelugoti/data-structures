#include <stdio.h>
#include <stdlib.h>

struct Node {
	int data;
	int height;
	int balance_factor; // height(root->right) - height(root->left)
	struct Node *left;
	struct Node *right;
};

struct Node* create(int data) {
	struct Node* node = (struct Node*) malloc(sizeof(struct Node));
	node->data = data;
	node->left = node->right = NULL;
	return node;
}

void _insert(struct Node *root, int data) {
	if(root == NULL || root->data == data)
		return;
	if(data < root->data) {
		if(root->left == NULL)
			root->left = create(data);
		else
			_insert(root->left, data);
	} else {
		if(root->right== NULL)
			root->right = create(data);
		else
			_insert(root->right, data);
	}
}

int _height(struct Node *node) {
	return node == NULL ? -1 : node->height;
}

int _max_height(struct Node *x, struct Node *y) {
	int a = _height(x);
	int b = _height(y);
	return a > b ? a : b;
}

void _update_height(struct Node *root) {
	if(root == NULL)
		return;
	_update_height(root->left);
	_update_height(root->right);
	root->height = 1 + _max_height(root->left, root->right);	
	root->balance_factor = _height(root->right) - _height(root->left);
}

void _balance(struct Node *root) {
	if(root == NULL)
		return;
	_balance(root->left);
	_balance(root->right);
	// TODO : implement rotations
}

void insert(struct Node *root, int data) {
	_insert(root, data);
	_update_height(root);
	_balance(root);
}

// Helper function to print the tree visually
void print_tree(struct Node *root, int space) {
	if(root == NULL)
		return;
	const int spacing = 8;
	space += spacing;
	print_tree(root->right, space);
	printf("\n");
	for (int i = spacing; i < space; i++) {
		printf(" ");
	}
	printf("%d,%d,%d\n", root->data, root->height, root->balance_factor);
	print_tree(root->left, space);
}


int main(int argc, char **argv) {
	struct Node *root = create(0);

	insert(root, 2);
	insert(root, 1);
	insert(root, 3);
	insert(root, -1);
	insert(root, -2);
	insert(root, -3);

	print_tree(root, 0);
	return 0;
}
