#include <stdlib.h>
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
	else if(y == y->parent->left)
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
				z->parent->parent->color = RED;
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
				z->parent->parent->color = RED;
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
		tree->root = z;
	else if(key < y->key)
		y->left = z;
	else
		y->right = z;

	insert_fixup(tree, z);
}

rb_node *get_node(rb_node *aux, rb_node *nil, int key) {
	if(aux == nil)
		return nil;
	else if(aux->key > key)
		return get_node(aux->left, nil, key);
	else if(aux->key < key)
		return get_node(aux->right, nil, key);
	else
		return aux;
}

void transplant(rb_tree *tree, rb_node *u, rb_node *v) {
	if(u->parent == tree->nil)
		tree->root = v;
	else if(u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;

	v->parent = u->parent;
}

rb_node *tree_minimum(rb_tree *tree, rb_node *x) {
	while(x->left != tree->nil)
		x = x->left;

	return x;
}

void delete_fixup(rb_tree *tree, rb_node *x) {
	while(x != tree->root && x->color == BLACK) {
		if(x == x->parent->left) {
			rb_node *w = x->parent->right;

			if(w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				left_rotate(tree, x->parent);
				w = x->parent->right;
			}

			if(w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->parent;
			} else {
				if(w->right->color == BLACK) {
					w->left->color = BLACK;
					w->color = RED;
					right_rotate(tree, w);
					w = x->parent->right;
				}

				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				left_rotate(tree, x->parent);
				x = tree->root;
			}
		} else {
			rb_node *w = x->parent->left;

			if(w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				right_rotate(tree, x->parent);
				w = x->parent->left;
			}

			if(w->right->color == BLACK && w->left->color == BLACK) {
				w->color = RED;
				x = x->parent;
			} else {
				if(w->left->color == BLACK) {
					w->right->color = BLACK;
					w->color = RED;
					left_rotate(tree, w);
					w = x->parent->left;
				}

				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				right_rotate(tree, x->parent);
				x = tree->root;
			}
		}
	}

	x->color = BLACK;
}

void delete(rb_tree *tree, int key) {
	rb_node *z = get_node(tree->root, tree->nil, key);

	if(z == tree->nil)
		return;

	rb_node *y = z, *x;
	rb_color y_original_color = y->color;

	if(z->left == tree->nil) {
		x = z->right;
		transplant(tree, z, z->right);
	} else if(z->right == tree->nil) {
		x = z->left;
		transplant(tree, z, z->left);
	} else {
		y = tree_minimum(tree, z->right);
		y_original_color = y->color;
		x = y->right;

		if(y->parent == z)
			x->parent = y;
		else {
			transplant(tree, y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}

		transplant(tree, z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}

	if(y_original_color == BLACK)
		delete_fixup(tree, x);
}
