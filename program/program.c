/*
	program.c
	A room painting invoice calculator. Foundation Progamming Assignment 1
	Kristian Welsh
	date
*/

#include <stdio.h>

void askName(char *namePtr);
int askWidth();
int askHeight(void);
int askLength(void);
char askPaintType(void);
int askUndercoatNeeded(void);
int askLabour(void);

void calculateInvoice(int width, int height, int length, char paintType, int undercoatNeeded, int labour);

int main(void)
{
	char name[32];
	int width, height, length;
	
	askName(name);
	width = askWidth();
	printf("Client Name: o %s\n", name);
	printf("Room Width: %d\n", width);
	return 0;
}

/*
	Asks the user for the client's name
	Accepts a pointer to a char array as an argument.
*/
void askName(char *namePtr)
{
	printf("Please enter client name: ");
	gets(namePtr);
}

int askWidth(void)
{
	int width;
	printf("Please enter room width: ");
	scanf("%d", &width);
	return width;
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

