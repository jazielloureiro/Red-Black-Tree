#ifndef RBTREE_H
#define RBTREE_H

typedef enum {
	RED, BLACK
} rb_color;

typedef struct Rb_node {
	int key;
	rb_color color;
	struct Rb_node *parent, *left, *right;
} rb_node;

typedef struct {
	rb_node *root, *nil;
} rb_tree;

rb_tree create_red_black_tree();

void insert(rb_tree *tree, int key);

#endif
