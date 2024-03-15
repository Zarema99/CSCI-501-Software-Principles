#include "Clock.h"
#include <stdio.h>
#include <stdlib.h>

Clock* createNewClock(int h, int m, int s){

	//Dynamic memory allocation
	Clock* clock_ptr = (Clock*)malloc(sizeof(Clock));

	//To be safe
	if (clock_ptr == NULL){
		printf("Warning: pointer has not been created!");
		return NULL;
	}

	if ( (h<0 || h>23) || (m<0 || m>59) || (s<0 || s>59) ){    //Checking whether h,m, and s are legal

			printf("Error: h, m, or s are inappropriate!\n");
			resetToMidnight(clock_ptr);

	}else{

		clock_ptr->hour = h;
		clock_ptr->minute = m;
		clock_ptr->second = s;

	}

	return clock_ptr;
}

void resetToMidnight(Clock *clk){

	clk->hour = 0;
	clk->minute = 0;
	clk->second = 0;

}

_Bool isMorning(Clock *clk){

	if (clk->hour>=0 && clk->hour<=11){

		return 1;    //True

	}else{

		return 0;    //False

	}
}

void advanceSeconds(Clock *clk, int secs){

	if (secs < 0){

		printf("Error: a negative value was entered for secs!\n");    //Checking whether secs is positive

	}else{

		int h_incr, m_incr, s_incr;

		h_incr = secs / 3600;    //integer division
		m_incr = (secs - h_incr*3600) / 60;    //integer division
		s_incr = secs - h_incr*3600 - m_incr*60;

		//Checking whether the addition of seconds results in a minute
		if ( (clk->second + s_incr) >= 60 ){

			m_incr++;
		}

		//Checking whether the addition of minutes results in an hour
		if ( (clk->minute + m_incr) >= 60 ){

			h_incr++;
		}

		clk->hour = (clk->hour + h_incr) % 24;    //From 0 to 23
		clk->minute = (clk->minute + m_incr) % 60;    //From 0 to 59
		clk->second = (clk->second + s_incr) % 60;    //From 0 to 59
	}
}

void printClock(Clock *clk){

	//When hour, minute, and/or second are from 0 to 9, we need to print an additional zero
	//The order of if statements matters

	if ( (clk->hour>=0 && clk->hour<=9) && (clk->minute>=0 && clk->minute<=9) && (clk->second>=0 && clk->second<=9) ){

		printf("0%i:0%i:0%i\n", clk->hour, clk->minute, clk->second);

	}else if ( (clk->hour>=0 && clk->hour<=9) && (clk->minute>=0 && clk->minute<=9) ){

		printf("0%i:0%i:%i\n", clk->hour, clk->minute, clk->second);

	}else if ( (clk->hour>=0 && clk->hour<=9) && (clk->second>=0 && clk->second<=9) ){

		printf("0%i:%i:0%i\n", clk->hour, clk->minute, clk->second);

	}else if ( (clk->minute>=0 && clk->minute<=9) && (clk->second>=0 && clk->second<=9) ){

		printf("%i:0%i:0%i\n", clk->hour, clk->minute, clk->second);

	}else if (clk->hour>=0 && clk->hour<=9){

		printf("0%i:%i:%i\n", clk->hour, clk->minute, clk->second);

	}else if (clk->minute>=0 && clk->minute<=9){

		printf("%i:0%i:%i\n", clk->hour, clk->minute, clk->second);

	}else if(clk->second>=0 && clk->second<=9){

		printf("%i:%i:0%i\n", clk->hour, clk->minute, clk->second);

	}
	else{

		printf("%i:%i:%i\n", clk->hour, clk->minute, clk->second);

	}
}
