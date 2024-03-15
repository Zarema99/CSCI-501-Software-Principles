#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


// Creates a new empty stack on the heap
stack* create_stack(){

	//Dynamically allocate memory for stack
	stack *stk_ptr = (stack*)malloc(sizeof(stack));

	stk_ptr->stack_size = 0;

	stk_ptr->top = NULL;

	return stk_ptr;
}

// Destroys the stack, and frees up its memory
void destroy_stack(stack *stk){

	if (stk->stack_size > 0){    //if stack size = 0, no need to destroy nodes

		//Destroying all nodes
		node *prev = stk->top;
		node *next = stk->top->link;

		while(next != NULL){

			//printf("Freeing %i\n", prev->value);    used to check the correctness of the code
			free(prev);
			prev = next;
			next = next->link;
		}
		//printf("Freeing %i\n", prev->value);    used to check the correctness of the code
		free(prev);
	}

	//Freeing the memory for stack
	free(stk);
}

// Adds the value val to the top of the stack
void push(stack *stk, int val){

	//Dynamically allocate a new node
	node *new_node = (node*)malloc(sizeof(node));

	new_node->value = val;
	new_node->link = stk->top;

	stk->top = new_node;
	stk->stack_size ++;
}

// Removes and returns the topmost item of the stack
int pop(stack *stk){

	//Checking if stack is empty
	if (stk->stack_size == 0){

		printf("Error: the stack is empty!\n");

		return INT_MIN;
	}

	//Pointer to the current top
	node *old_top = stk->top;

	//New top is a next node
	stk->top = stk->top->link;

	//Old top value
	int top_old_val = old_top->value;

	//printf("Freeing %i\n", old_top->value);    used to check the correctness of the code

	//Freeing memory for the old top
	free(old_top);

	stk->stack_size --;

	return top_old_val;
}

// Returns the topmost item of the stack, without changing the stack
int peek_top(stack *stk){

	return stk->top->value;
}

// Returns the number of items on the stack
size_t stack_size(stack *stk){

	return stk->stack_size;
}

// Removes all of the items from the stack
void clear_stack(stack *stk){

	if (stk->stack_size > 0){    //if stack size = 0, no need to clear

		//Destroying all nodes
		node *prev = stk->top;
		node *next = stk->top->link;

		while(next != NULL){

			//printf("Freeing %i\n", prev->value);    used to check the correctness of the code
			free(prev);
			prev = next;
			next = next->link;
		}
		//printf("Freeing %i\n", prev->value);    used to check the correctness of the code
		free(prev);

		//Set stack size to zero and top to NULL
		stk->stack_size = 0;
		stk->top = NULL;
	}
}

// Outputs the items in the stack to the console window (from top to bottom)
void print_stack(stack *stk){

	printf("top [ ");

	//Temporary node
	node *temp = stk->top;

	while (temp != NULL){

		printf("%i", temp->value);

		if (temp->link != NULL){

			printf(", ");

		}

		temp = temp->link;
	}

	printf(" ] bottom\n");
}
