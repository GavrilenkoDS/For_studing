#include <stdio.h>
#include <stdlib.h>

int min(int a, int b) {
	if (a > b)
		return b;
	else return a;
}

int max(int a, int b) {
	if (a < b)
		return b;
	else return a;
}

struct node {
	int key;
	int data;
	struct node *left;
	struct node *right;
	struct node *parent;
};

struct node * find(struct node *tree, int key) {
	if (key == tree->key)
		return tree;
	if (key > tree->key) {
		if (tree->left != NULL)
			find(tree->left, key);
		else
			return 0;
	}
	if (key < tree->key) {
		if (tree->right != NULL)
			find(tree->right, key);
		else
			return 0;
	}
}

int total(struct node *tree) {
	int sum=0;
	if (tree != NULL) { 
		sum+= tree->data; 
		sum+=total(tree->left);
		sum+=total(tree->right);
	}
	return sum;
}

int height(struct node *tree) {
	if (tree==NULL) return -1;
	return 1 + max(height(tree->left), height(tree->right));
}

int minn(struct node *tree) {
	if (tree == NULL) return -1;
	return min(minn(tree->left), minn(tree->right));
}



void destroy(struct node *tree) {
	if (tree != NULL) {
		destroy(tree->left);
		destroy(tree->right);
	}
	free(tree);
}

struct node *cloneNode(struct node *root) {
	struct node *new_root;
	new_root = (struct node*) malloc (sizeof(struct node));
	new_root->data = root->data;
	return new_root;
}

void copy(struct node *orgTree, struct node * copyTree) {
	if (orgTree != NULL) {
		//left side
		struct node *newLeftNode = cloneNode(orgTree->left);
		copyTree->left = newLeftNode;
		copy(orgTree->left, copyTree->left);

		//right side
		struct node *newRightNode = cloneNode(orgTree->right);
		copyTree->right = newRightNode;
		copy(orgTree->right, copyTree->right);
	}
}

int main() {


}