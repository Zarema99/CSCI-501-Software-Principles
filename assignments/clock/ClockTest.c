#include "Clock.h"
#include <stdio.h>
#include<stdlib.h>

int main(void) {

	Clock *clk_ptr = createNewClock(20, 13, 5);
	printClock(clk_ptr);
	_Bool morning = isMorning(clk_ptr);
	printf("%i\n", morning);    //must be 0

	printf("\n");

	advanceSeconds(clk_ptr, 9165);
	printClock(clk_ptr);    //must be 22:45:50
	morning = isMorning(clk_ptr);
	printf("%i\n", morning);    //must be 0

	printf("\n");

	advanceSeconds(clk_ptr, 8000);
	printClock(clk_ptr);    //must be 00:59:10
	morning = isMorning(clk_ptr);
	printf("%i\n", morning);    //must be 1

	printf("\n");

	resetToMidnight(clk_ptr);
	printClock(clk_ptr);    //must be 00:00:00
	morning = isMorning(clk_ptr);
	printf("%i\n", morning);    //must be 1

	printf("\n");

	advanceSeconds(clk_ptr, 6982);
	printClock(clk_ptr);    //must be 01:56:22
	morning = isMorning(clk_ptr);
	printf("%i\n", morning);    //must be 1

	printf("\n");

	advanceSeconds(clk_ptr, 293);
	printClock(clk_ptr);    //must be 02:01:15
	morning = isMorning(clk_ptr);
	printf("%i\n", morning);    //must be 1

	printf("\n");

	advanceSeconds(clk_ptr, 0);
	printClock(clk_ptr);    //must be 02:01:15
	morning = isMorning(clk_ptr);
	printf("%i\n", morning);    //must be 1

	printf("\n");

	advanceSeconds(clk_ptr, -8000);    //error

	printf("\n");

	Clock *clk_ptr2 = createNewClock(25, 45, -1);    //error
	printClock(clk_ptr2);    //must be 00:00:00
	morning = isMorning(clk_ptr2);
	printf("%i\n", morning);    //must be 1

	//Freeing memory
	free(clk_ptr);
	free(clk_ptr2);

	return 0;
}

