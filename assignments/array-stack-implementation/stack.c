#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Creates a new empty stack on the heap
stack* create_stack(){

	//Dynamically allocate memory for stack
	stack *stk_ptr = (stack*)malloc(sizeof(stack));

	stk_ptr->stack_size = 0;
	stk_ptr->array_size = 5;	//can be different

	//Dynamically allocate memory for array
	stk_ptr->values = (int*)calloc(stk_ptr->array_size, sizeof(int));

	return stk_ptr;
}

// Destroys the stack, and frees up its memory
void destroy_stack(stack *stk){

	//Free memory for array
	free(stk->values);

	//Free memory for stack
	free(stk);
}

// Adds the value val to the top of the stack
void push(stack *stk, int val){

	if (stk->stack_size < stk->array_size){

		//Pointer arithmetics
		*(stk -> values + stk->stack_size) = val;
		stk->stack_size ++;

	}else{

		//Double array size and dynamically allocate memory
		stk->array_size = 2*stk->array_size;
		int *values_new = (int*)calloc(stk->array_size, sizeof(int));

		int i;

		//Copying values
		for (i = 0; i < stk->array_size/2; i++){

			*(values_new + i) = *(stk -> values + i);
			//printf("Copying %i\n", *(stk -> values + i));    used to check the correctness of the code
		}

		//Free memory for old array
		free(stk->values);

		stk->values = values_new;

		*(stk -> values + stk->stack_size) = val;
		stk->stack_size ++;
	}
}

// Removes and returns the topmost item of the stack
int pop(stack *stk){

	//Checking if stack is empty
	if (stk->stack_size == 0){

		printf("Error: the stack is empty!\n");

		return INT_MIN;
	}

	//Old top value
	int top_old = peek_top(stk);

	stk->stack_size --;

	return top_old;
}

// Returns the topmost item of the stack, without changing the stack
int peek_top(stack *stk){

	int top = *(stk -> values + stk -> stack_size - 1);

	return top;
}

// Returns the number of items on the stack
size_t stack_size(stack *stk){

	return stk->stack_size;
}

// Removes all of the items from the stack
void clear_stack(stack *stk){

	//Set stack size to zero
	stk->stack_size = 0;
}

// Outputs the items in the stack to the console window (from bottom to top)
void print_stack(stack *stk){

	int i;

	printf("bottom [ ");

	for (i = 0; i < stk->stack_size; i++){

		if (i != 0){
			printf(", ");
		}

		printf("%i", *(stk -> values + i));
	}

	printf(" ] top\n");

}
