/*
	program.c
	A room painting invoice calculator. Foundation Progamming Assignment 1
	Kristian Welsh
	date
*/

#include <stdio.h>

void askName(char *namePtr);
int askWidth(void);
int askHeight(void);
int askLength(void);
char askPaintType(void);
int askUndercoatNeeded(void);
int askLabour(void);

void calculateInvoice(int width, int height, int length, char paintType, int undercoatNeeded, int labour);

int main(void)
{
	char name[32];
	askName(name);
	printf("hello %s!", name);
	return 0;
}


void askName(char *namePtr)
{
	char name[32];
	printf("Please enter your name: ");
	gets(namePtr);
}

int askWidth(void)
{
	
}

int askHeight(void)
{
	
}

int askLength(void)
{
	
}

char askPaintType(void)
{
	
}

int askUndercoatNeeded(void)
{
	
}

int askLabour(void)
{
	
}


void calculateInvoice(int width, int height, int length, char paintType, int undercoatNeeded, int labour)
{
	
}

