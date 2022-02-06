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

void insert_fixup(rb_tree *tree, rb_node *z) {
	while(z->parent->color == RED) {
		if(z->parent == z->parent->parent->left) {
			rb_node *y = z->parent->parent->right;

			if(y->color == RED) {
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent = RED;
				z = z->parent->parent;
			} else {
				if(z == z->parent->right) {
					z = z->parent;
					left_rotate(tree, z);
				}

				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				right_rotate(tree, z->parent->parent);
			}
		} else {
			rb_node *y = z->parent->parent->left;

			if(y->color == RED) {
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent = RED;
				z = z->parent->parent;
			} else {
				if(z == z->parent->left) {
					z = z->parent;
					right_rotate(tree, z);
				}

				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				left_rotate(tree, z->parent->parent);
			}
		}
	}

	tree->root->color = BLACK;
}
