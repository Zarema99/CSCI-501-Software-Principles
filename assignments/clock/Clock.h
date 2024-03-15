#ifndef CLOCK_H_
#define CLOCK_H_

//Defining the type Clock
typedef struct {
	int hour;
	int minute;
	int second;
} Clock;

//Function signatures

Clock* createNewClock(int h, int m, int s);

void resetToMidnight(Clock *clk);

_Bool isMorning(Clock *clk);

void advanceSeconds(Clock *clk, int secs);

void printClock(Clock *clk);

#endif
