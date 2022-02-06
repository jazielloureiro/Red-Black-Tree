#ifndef RBTREE_H
#define RBTREE_H

typedef struct {
	rb_node *root, *nil;
} rb_tree;

rb_tree create_red_black_tree();

void insert(rb_tree *tree, int key);

#endif
