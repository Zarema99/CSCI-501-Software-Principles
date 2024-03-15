#include "stack.h"
#include <stdio.h>
#include <stdlib.h>


int main(void){

	//Creating a stack
	stack *stk_ptr = create_stack();

	push(stk_ptr, 5);
	print_stack(stk_ptr);

	push(stk_ptr, 10);
	print_stack(stk_ptr);

	int i;

	//Push 15 elements
	for (i = 0; i < 15; i++){

		push(stk_ptr, i);
	}
	print_stack(stk_ptr);

	int size = stack_size(stk_ptr);
	printf("Size: %i\n", size);

	int old_top = pop(stk_ptr);
	print_stack(stk_ptr);
	printf("Old top: %i\n", old_top);

	//Clearing stack
	clear_stack(stk_ptr);
	print_stack(stk_ptr);

	//Push 5 elements
	for (i = 0; i < 5; i++){

		push(stk_ptr, 5*i);
	}
	print_stack(stk_ptr);

	int top = peek_top(stk_ptr);
	printf("Top: %i\n", top);

	old_top = pop(stk_ptr);
	print_stack(stk_ptr);
	printf("Old top: %i\n", old_top);

	old_top = pop(stk_ptr);
	print_stack(stk_ptr);
	printf("Old top: %i\n", old_top);

	top = peek_top(stk_ptr);
	print_stack(stk_ptr);
	printf("Top: %i\n", top);

	size = stack_size(stk_ptr);
	printf("Size: %i\n", size);

	//Destroy stack
	destroy_stack(stk_ptr);



	//Creating another stack
	stack *stk_ptr2 = create_stack();

	//Clearing empty stack
	clear_stack(stk_ptr2);
	printf("\n");
	print_stack(stk_ptr2);

	//Checking for error
	old_top = pop(stk_ptr2);
	printf("Old top: %i\n", old_top);

	size = stack_size(stk_ptr2);
	printf("Size: %i\n", size);

	//Destroy stack
	destroy_stack(stk_ptr2);

	return 0;
}


