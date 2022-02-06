#include <stdio.h>
#include "rbtree.h"

int count_nodes(rb_node *aux, rb_node *nil) {
	if(aux == nil)
		return 0;

	return 1 + count_nodes(aux->left, nil) + count_nodes(aux->right, nil);
}

int main() {
	printf("Hello World!\n");
	return 0;
}
