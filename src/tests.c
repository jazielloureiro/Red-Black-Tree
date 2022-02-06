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

int count_nodes(rb_node *aux, rb_node *nil) {
	if(aux == nil)
		return 0;

	return 1 + count_nodes(aux->left, nil) + count_nodes(aux->right, nil);
}

int main() {
	const int keys_qty = 10;
	int *keys = get_keys(keys_qty);

	free(keys);

	return 0;
}
