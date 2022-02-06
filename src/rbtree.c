#include <stdlib.h>

typedef enum {
	RED, BLACK
} rb_color;

typedef struct Rb_node {
	int key;
	rb_color color;
	struct Rb_node *parent, *left, *right;
} rb_node;

#include "rbtree.h"

rb_tree create_red_black_tree() {
	rb_tree tree;

	tree.nil = malloc(sizeof(rb_node));
	tree.nil->color = BLACK;
	tree.root = tree.nil;

	return tree;
}

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

void insert(rb_tree *tree, int key) {
	rb_node *x = tree->root, *y = tree->nil;

	while(x != tree->nil) {
		y = x;

		if(key < x->key)
			x = x->left;
		else
			x = x->right;
	}

	rb_node *z = malloc(sizeof(rb_node));
	z->key = key;
	z->color = RED;
	z->parent = y;
	z->left = tree->nil;
	z->right = tree->nil;

	if(y == tree->nil)
		tree->root;
	else if(key < y->key)
		y->left = z;
	else
		y->right = z;

	insert_fixup(tree, z);
}
