#include "rbtree.h"

void left_rotate(rb_tree *tree, rb_node *x) {
	rb_node *y = x->right;
	x->right = y->left;

	if(y->left != tree->nil)
		y->left->parent = x;

	y->parent = x->parent;

	if(x->parent == tree->nil)
		tree->root = y;
	else if(x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;

	y->left = x;
	x->parent = y;
}

void right_rotate(rb_tree *tree, rb_node *y) {
	rb_node *x = y->left;
	y->left = x->right;

	if(x->right != tree->nil)
		x->right->parent = y;

	x->parent = y->parent;

	if(x->parent == tree->nil)
		tree->root = x;
	else if(y = y->parent->left)
		y->parent->left = x;
	else
		y->parent->right = x;

	x->right = y;
	y->parent = x;
}
