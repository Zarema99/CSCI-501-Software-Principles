#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// Creates a new empty map on the heap
map* create_map(){

	//Dynamically allocate memory for map
	map *map_ptr = (map*)malloc(sizeof(map));

	map_ptr->map_size = 0;
	map_ptr->root = NULL;

	return map_ptr;
}

void free_recursive(tree_node *node){

	if (node != NULL) {

		free_recursive(node->left);
		free_recursive(node->right);

		//printf("Freeing memory for %s\n", node->key);    //used for checking the correctness

		free(node);
	}
}

// Destroys the map, and frees up its memory
void destroy_map(map *mp){

	//Free nodes
	free_recursive(mp->root);

	//Free map
	free(mp);
}



// Adds the key-value pair (key, val) to the map
void define(map *mp, char *key, int val){

	if (mp->root == NULL){    //adding the first node

		//Dynamically allocate a new node
		tree_node *new_node = (tree_node*)malloc(sizeof(tree_node));
		new_node->left = NULL;
		new_node->right = NULL;
		new_node->key = key;
		new_node->value = val;

		mp->root = new_node;
		mp->map_size ++;

	}else{
		tree_node *temp = mp->root;
		tree_node *parent;
		int cmp;

		//Traverse and compare keys
		while (temp != NULL){

			parent = temp;
			cmp = strcmp(key, temp->key);

				if (cmp == 0){

					temp->value = val;    //found -> change value
					break;

				}else if (cmp < 0){    //Go to the left subtree

					temp = temp->left;

				}else{    //Go to the right subtree

					temp = temp->right;
				}
		}

		if (cmp != 0){    //Not found

			//Dynamically allocate a new node
			tree_node *new_node = (tree_node*)malloc(sizeof(tree_node));
			new_node->left = NULL;
			new_node->right = NULL;
			new_node->key = key;
			new_node->value = val;
			mp->map_size ++;

			if (cmp < 0){

				parent->left = new_node;

			}else{

				parent->right = new_node;

			}
		}
	}
}

// Checks if the given key is in the map
_Bool contains_key(map *mp, char *key){

	tree_node *temp = mp->root;
	int cmp;

	while (temp != NULL){

		cmp = strcmp(key, temp->key);

		if (cmp == 0){    //found

			break;

		}else if (cmp < 0){

			temp = temp->left;

		}else{

			temp = temp->right;

		}
	}

	return temp != NULL;
}


// Returns the value associated with the given key;
// If the key is not there, output an error message to the
// console window, and return INT_MIN
int get_value(map *mp, char *key){

	_Bool is_there;

	is_there = contains_key(mp, key);

	if (is_there == 0){    //does not contain -> error

		printf("Error: the given key is not in the map!\n");
		return INT_MIN;

	}else{

		tree_node *temp = mp->root;
		int cmp;

		while (temp != NULL){

			cmp = strcmp(key, temp->key);

			if (cmp == 0){    //Found

				break;

			}else if (cmp < 0){

				temp = temp->left;

			}else{

				temp = temp->right;
			}
		}
		return temp->value;
	}
}

// Returns the number of key-value pairs in the map
size_t map_size(map *mp){

	return mp->map_size;
}

// Removes all of the key-value pairs from the map
void clear_map(map *mp){

	//Free nodes
	free_recursive(mp->root);

	mp->map_size = 0;
	mp->root = NULL;
}

void print_recursive(tree_node *node){

	if (node != NULL) {

		printf("%s: %i >> ", node->key, node->value);

		print_recursive(node->left);
		print_recursive(node->right);
	}
}

// Outputs the key-value pairs in the map to the console window
void print_map(map *mp){

	printf("[ ");

	print_recursive(mp->root);

	printf("]\n");
}


