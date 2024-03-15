#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){

	//Creating a map
	map *map_ptr = create_map();

	define(map_ptr, "bananas", 5);
	print_map(map_ptr);

	define(map_ptr, "apples", 2);
	print_map(map_ptr);

	double l_f = load_factor(map_ptr);
	printf("Load factor: %lf\n", l_f);    //must be 0.5

	//Clear map
	clear_map(map_ptr);
	print_map(map_ptr);

	int size = map_size(map_ptr);
	printf("Size: %i\n", size);    //must be 0

	define(map_ptr, "carrots", 3);
	print_map(map_ptr);

	define(map_ptr, "apples", 1);
	print_map(map_ptr);

	define(map_ptr, "grapes", 11);
	print_map(map_ptr);

	define(map_ptr, "oranges", 8);
	print_map(map_ptr);

	define(map_ptr, "pears", 9);
	print_map(map_ptr);

	define(map_ptr, "potatoes", 5);
	print_map(map_ptr);

	//must overwrite
	define(map_ptr, "grapes", 24);
	print_map(map_ptr);

	define(map_ptr, "tomatoes", 0);
	print_map(map_ptr);

	size = map_size(map_ptr);
	printf("Size: %i\n", size);    //must be 7

	define(map_ptr, "peaches", 7);
	print_map(map_ptr);

	define(map_ptr, "cucumbers", 12);
	print_map(map_ptr);

	define(map_ptr, "plums", 4);
	print_map(map_ptr);

	define(map_ptr, "zucchinis", 6);
	print_map(map_ptr);

	define(map_ptr, "lemons", 3);
	print_map(map_ptr);

	l_f = load_factor(map_ptr);
	printf("Load factor: %lf\n", l_f);    //must be 3

	double stdev = bucket_size_stdev(map_ptr);
	printf("Stdev: %lf\n", stdev);

	define(map_ptr, "bananas", 1);
	print_map(map_ptr);

	define(map_ptr, "kiwis", 2);
	print_map(map_ptr);

	define(map_ptr, "apricots", 17);
	print_map(map_ptr);

	define(map_ptr, "grapefruits", 3);
	print_map(map_ptr);

	define(map_ptr, "pineapples", 7);
	print_map(map_ptr);

	define(map_ptr, "limes", 2);
	print_map(map_ptr);

	define(map_ptr, "peppers", 13);
	print_map(map_ptr);

	define(map_ptr, "raspberries", 35);
	print_map(map_ptr);

	define(map_ptr, "strawberries", 40);
	print_map(map_ptr);

	define(map_ptr, "cherries", 15);
	print_map(map_ptr);

	define(map_ptr, "mangos", 4);
	print_map(map_ptr);

	define(map_ptr, "watermelons", 1);
	print_map(map_ptr);

	l_f = load_factor(map_ptr);
	printf("Load factor: %lf\n", l_f);    //must be 3

	stdev = bucket_size_stdev(map_ptr);
	printf("Stdev: %lf\n", stdev);

	define(map_ptr, "Watermelons", 1);
	print_map(map_ptr);

	//must overwrite
	define(map_ptr, "peppers", 12);
	print_map(map_ptr);

	int is_there = contains_key(map_ptr, "apricots");
	printf("Contains: %i\n", is_there);    //must be 1

	is_there = contains_key(map_ptr, "Corns");
	printf("Contains: %i\n", is_there);    //must be 0

	int value = get_value(map_ptr, "peppers");
	printf("Value: %i\n", value);    //must be 12

	value = get_value(map_ptr, "watermelons");
	printf("Value: %i\n", value);    //must be 1

	//Checking error
	value = get_value(map_ptr, "avocados");
	printf("Value: %i\n", value);

	l_f = load_factor(map_ptr);
	printf("Load factor: %lf\n", l_f);    //must be 1.5625

	stdev = bucket_size_stdev(map_ptr);
	printf("Stdev: %lf\n", stdev);

	size = map_size(map_ptr);
	printf("Size: %i\n", size);    //must be 25

	//Destroy map
	destroy_map(map_ptr);

	return 0;
}


