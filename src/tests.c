#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "rbtree.h"
 
int *get_keys(int keys_qty) {
	int *keys = malloc(sizeof(int) * keys_qty);

	srand(time(NULL));

	for(int i = 0; i < keys_qty; ) {
		bool is_key_repeated = true;
		int new_key = rand();

		for(int j = i - 1; j >= 0 && is_key_repeated; j--)
			if(new_key == keys[j])
				is_key_repeated = false;

		if(is_key_repeated) {
			keys[i] = new_key;
			i++;
		}
	}

	return keys;
}

int black_height_traversal(rb_node *aux, rb_node *nil) {
	if(aux == nil)
		return 1;

	int left_height = black_height_traversal(aux->left, nil),
	    right_height = black_height_traversal(aux->right, nil);

	if(left_height != right_height || left_height == -1)
		return -1;
	else
		return left_height + (aux->color == BLACK? 1 : 0);
}

int get_black_height(rb_node *aux, rb_node *nil) {
	if(aux == nil)
		return 1;

	int left_height = black_height_traversal(aux->left, nil),
	    right_height = black_height_traversal(aux->right, nil);

	if(left_height != right_height || left_height == -1)
		return -1;
	else
		return left_height;
}

bool is_red_black_tree(rb_node *aux, rb_node *nil) {
	if(aux == nil)
		return true;

	if(get_black_height(aux, nil) != -1)
		if(is_red_black_tree(aux->left, nil))
			return is_red_black_tree(aux->right, nil);

	return false;
}

int count_nodes(rb_node *aux, rb_node *nil) {
	if(aux == nil)
		return 0;

	return 1 + count_nodes(aux->left, nil) + count_nodes(aux->right, nil);
}

int main() {
	rb_tree tree = create_red_black_tree();
	const int keys_qty = 10000;
	int *keys = get_keys(keys_qty);

	printf("Inserting %d keys.\n", keys_qty);
	for(int i = 0; i < keys_qty; i++)
		insert(&tree, keys[i]);

	int nodes_qty = count_nodes(tree.root, tree.nil);

	if(keys_qty == nodes_qty)
		puts("All keys were inserted.");
	else {
		printf("Something unexpected happened. %d keys were inserted.\n", nodes_qty);
		exit(EXIT_FAILURE);
	}

	if(is_red_black_tree(tree.root, tree.nil))
		puts("The tree is still a red black tree.");
	else {
		puts("The tree isn't a red black tree anymore.");
		exit(EXIT_FAILURE);
	}

	int delete_qty = keys_qty / 10;
	printf("Deleting %d keys.\n", delete_qty);
	for(int i = 0; i < keys_qty; i += 10)
		delete(&tree, keys[i]);

	nodes_qty = count_nodes(tree.root, tree.nil);

	if(keys_qty - delete_qty == nodes_qty)
		puts("All keys were deleted.");
	else {
		printf("Something unexpected happened. %d keys are in the tree.\n", nodes_qty);
		exit(EXIT_FAILURE);
	}

	if(is_red_black_tree(tree.root, tree.nil))
		puts("The tree is still a red black tree.");
	else {
		puts("The tree isn't a red black tree anymore.");
		exit(EXIT_FAILURE);
	}

	free(keys);

	return 0;
}
