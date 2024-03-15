#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>


// Creates a new empty map on the heap
map* create_map(){

	//Dynamically allocate memory for map
	map *map_ptr = (map*)malloc(sizeof(map));

	map_ptr->map_size = 0;
	map_ptr->num_of_buckets = INITIAL_BUCKETS;

	//Dynamically allocate memory for buckets
	map_ptr->buckets = (node**)calloc(map_ptr->num_of_buckets, sizeof(node*));

	size_t i;
	for (i = 0; i < map_ptr->num_of_buckets; i++){

		map_ptr->buckets[i] = NULL;
	}

	return map_ptr;
}

void free_recursive(node* node){

	if (node != NULL) {

		free_recursive(node->link);

		printf("Freeing memory for %s\n", node->key);    //used for checking the correctness

		free(node);
	}
}

// Destroys the map, and frees up its memory
void destroy_map(map *mp){

	//Free nodes
	size_t i;
	for (i = 0; i < mp->num_of_buckets; i++){

		free_recursive(mp->buckets[i]);
	}

	//Free buckets
	free(mp->buckets);

	//Free map
	free(mp);

}

//Hash function
int hash_function(char *key) {

	int hash_value = 0;
	size_t i;

	for (i = 0; i < strlen(key); i++){

		hash_value = key[i]*pow(31, strlen(key)-1-i) + hash_value;    //java hash function
	}

	return hash_value;
}


// Adds the key-value pair (key, val) to the map
void define(map *mp, char *key, int val){

	//Mode operator to choose a bucket
	int bucket = hash_function(key) % mp->num_of_buckets;

	//Load factor
	double l_f = load_factor(mp);

	if (l_f < MAX_LOAD_FACTOR){

		if (mp->buckets[bucket] == NULL){    //Adding the first element to a bucket

			//Dynamically allocate a new node
			node *new_node = (node*)malloc(sizeof(node));

			new_node->link = NULL;
			new_node->key = key;
			new_node->value = val;
			mp->map_size ++;

			mp->buckets[bucket] = new_node;
		}

		else{    //Traverse and compare

			int cmp;

			node *temp = mp->buckets[bucket];
			node *prev;

			while(temp != NULL){

				prev = temp;

				cmp = strcmp(key,  temp -> key);

				if (cmp == 0){    //Found -> change value

					temp->value = val;
					break;
				}

				temp = temp->link;
			}

			if (cmp != 0){

				//Dynamically allocate a new node
				node *new_node = (node*)malloc(sizeof(node));

				new_node->link = NULL;
				new_node->key = key;
				new_node->value = val;
				mp->map_size ++;

				prev->link = new_node;
			}
		}

	}else{    //Double the size of buckets and rehash

		mp->num_of_buckets = 2*mp->num_of_buckets;

		node **buckets_new = (node**)calloc(mp->num_of_buckets, sizeof(node*));

		size_t i;
		for (i = 0; i < mp->num_of_buckets; i++){

			buckets_new[i] = NULL;
		}

		//Rehashing (no need to traverse and compare)

		for (i = 0; i < mp->num_of_buckets/2; i++){

			node *temp_node = mp->buckets[i];

			while(temp_node != NULL){

				//Mode operator to choose a new bucket
				int new_bucket = hash_function(temp_node->key) % mp->num_of_buckets;

				//Dynamically allocate a new node
				node *new_node = (node*)malloc(sizeof(node));

				new_node->link = buckets_new[new_bucket];
				new_node->key = temp_node->key;
				new_node->value = temp_node->value;

				buckets_new[new_bucket] = new_node;

				//printf("Rehashing %s\n", new_node->key);    //used for checking the correctness

				temp_node = temp_node->link;
			}
		}

		//Free old nodes
		for (i = 0; i < mp->num_of_buckets/2; i++){

			free_recursive(mp->buckets[i]);
		}

		//Free old buckets
		free(mp->buckets);

		mp->buckets = buckets_new;

		//Add a new element
		int bucket = hash_function(key) % mp->num_of_buckets;

		if (mp->buckets[bucket] == NULL){    //Adding the first element to a bucket

			//Dynamically allocate a new node
			node *new_node = (node*)malloc(sizeof(node));

			new_node->link = NULL;
			new_node->key = key;
			new_node->value = val;

			mp->map_size ++;

			mp->buckets[bucket] = new_node;
			}

			else{    //Traverse and compare

				int cmp;

				node *temp = mp->buckets[bucket];
				node *prev;

				while(temp != NULL){

					prev = temp;

					cmp = strcmp(key,  temp -> key);

					if (cmp == 0){

						temp->value = val;    //Found -> change value
						break;
					}

					temp = temp->link;
				}


				if (cmp != 0){

					//Dynamically allocate a new node
					node *new_node = (node*)malloc(sizeof(node));

					new_node->link = NULL;
					new_node->key = key;
					new_node->value = val;

					mp->map_size ++;

					prev->link = new_node;
				}
			}
	}
}

// Checks if the given key is in the map
_Bool contains_key(map *mp, char *key){

	//Mode operator to choose a needed bucket
	int bucket = hash_function(key) % mp->num_of_buckets;

	int cmp;
	node *temp = mp->buckets[bucket];

	while(temp != NULL){    //Traverse and compare

		cmp = strcmp(key, temp -> key);

		if (cmp == 0){    //found

			break;
		}

		temp = temp->link;
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

		//Mode operator to choose a needed bucket
		int bucket = hash_function(key) % mp->num_of_buckets;

		node *temp = mp->buckets[bucket];
		int cmp;

		while (temp != NULL){

			cmp = strcmp(key, temp->key);

			if (cmp == 0){    //Found

				break;
			}

			temp = temp->link;
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
	size_t i;
	for (i = 0; i < mp->num_of_buckets; i++){

		free_recursive(mp->buckets[i]);
	}

	mp->map_size = 0;

	for (i = 0; i < mp->num_of_buckets; i++){

		mp->buckets[i] = NULL;
	}
}

void print_recursive(node *node){

	if (node != NULL) {

		printf("%s: %i >> ", node->key, node->value);

		print_recursive(node->link);
	}
}

// Outputs the key-value pairs in the map to the console window
void print_map(map *mp){

	size_t i;
	printf("[ ");
	for (i = 0; i < mp->num_of_buckets; i++){

		print_recursive(mp->buckets[i]);
	}
	printf("]\n");
}

// Outputs the load factor of the underlying hash table
double load_factor(map *mp){

	return (double)mp->map_size / mp->num_of_buckets;
}

// Outputs the standard deviation of the sizes of the buckets
// in the underlying hash table
double bucket_size_stdev(map *mp){

	size_t i;
	double sum = 0;
	double l_f = load_factor(mp);
	double dif, dif_sqrd;

	for (i = 0; i < mp->num_of_buckets; i++){

		int size_of_bucket = 0;
		node *temp = mp->buckets[i];

		while(temp != NULL){

			size_of_bucket ++;
			temp = temp->link;
		}

		//printf("size: %i\n", size_of_bucket);    used for checking the correctness
		dif = size_of_bucket - l_f;
		dif_sqrd = dif*dif;

		sum = sum + dif_sqrd;
	}

	return sqrt(sum / mp->num_of_buckets);
}

