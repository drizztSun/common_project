#include<stdio.h>
#include<stdlib.h>

struct btreenode {
	int data;
	struct btreenode* left;
	struct btreenode* right;
};

void freeall(btreenode* tree) {
	if (tree == NULL) {
		return;
	}
	free(tree);
	freeall(tree->left);
	freeall(tree->right);


}



void preorder_travel(btreenode* a) {
	if (a == NULL)
		return;
	

	if (a->left == NULL && a->right == NULL)
		printf("%d", a->data);
		

	printf(" %d", a->data);
	preorder_travel(a->left);
	preorder_travel(a->right);
	return;
}

void inorder_travel(btreenode* a) {
	if (a == NULL) 
		return;

	if (a->left == NULL && a->right == NULL) 
		printf("%d", a->data);
	
	preorder_travel(a->left); 
	printf(" %d", a->data);
	preorder_travel(a->right);
	return;
}


void postorder_travel(btreenode* a) {
	if (a == NULL) 
		return;

	if (a->left == NULL && a->right == NULL) 
		printf("%d", a->data);
	
	preorder_travel(a->left);
	preorder_travel(a->right);
	printf(" %d", a->data);
	return;
}





//DIY, 1) don't repeat yourself
btreenode* make_treenode(int data = 0) {
	btreenode* a = (btreenode*)malloc(sizeof(btreenode));
	a->data = data;
	a->left = NULL;
	a->right = NULL;
	return a;
}

btreenode maketree() {
	btreenode node;
	node.data = 1;


	btreenode* node2p = make_treenode(2);
	node.left = node2p;


	btreenode* node3p = make_treenode(3);
	node.right = node3p;

	btreenode* node4p = make_treenode(4);
	node2p->left = node4p;
	

	btreenode* node5p = make_treenode(5);
	node2p->right = node5p;


	btreenode* node6p = make_treenode(6);
	node3p->left = node6p;


	return node;
}

int tbtree() {

	btreenode a = maketree();

	freeall(&a);

	return 0;
}
	