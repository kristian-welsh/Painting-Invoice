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

void calculateInvoice(int, int, int, char, int, int);

void displayClientName(char *namePtr);
void displayWidth(int);
void displayHeight(int);
void displayLength(int);
void displayPaintType(char);

int main(void) {
  char name[32], paintType, undercoatNeeded, foo;
  int width, height, length, labourHours;
  
  askName(name);
  width = askWidth();
  height = askHeight();
  length = askLength();
  paintType = askPaintType();
  undercoatNeeded = askUndercoatNeeded();
  labourHours = askLabour();

  displayClientName(name);
  displayWidth(width);
  displayHeight(height);
  displayLength(length);
  displayPaintType(paintType);
  printf("Undercoat Needed: %c\n", undercoatNeeded);
  printf("Labour Hours Needed: %d\n", labourHours);

  /* Halt program for user to see output - Later i plan to replace this with a simpler method */
  printf("Press ENTER to exit...");
  scanf("%c", &foo);
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
  fflush(stdin);
}

int askWidth(void)
{
  int width;
  printf("Please enter room width: ");
  scanf("%d", &width);
  fflush(stdin);
  return width;
}

int askHeight(void)
{
  int height;
  printf("Please enter room height: ");
  scanf("%d", &height);
  fflush(stdin);
  return height;
}

int askLength(void)
{
  int length;
  printf("Please enter room length: ");
  scanf("%d", &length);
  fflush(stdin);
  return length;
}

char askPaintType(void)
{
  char paintType;
  printf("Please enter paint type: ");
  scanf("%c", &paintType);
  fflush(stdin);
  return paintType;
}

int askUndercoatNeeded(void)
{
  char undercoatNeeded;
  printf("Please enter Y if an undercoat is needed, otherwise enter N: ");
  scanf("%c", &undercoatNeeded);
  fflush(stdin);
  return undercoatNeeded;
}

int askLabour(void)
{
  int labourHours;
  printf("Please enter how many hours labour will be needed: ");
  scanf("%d", &labourHours);
  fflush(stdin);
  return labourHours;
}


void calculateInvoice(int width, int height, int length, char paintType, int undercoatNeeded, int labour)
{
  
}

void displayClientName(char *namePtr)
{
  printf("Client Name: %s\n", namePtr);
}

void displayWidth(int width)
{
  printf("Room width: %d\n", width);
}

void displayHeight(int height)
{
  printf("Room height: %d\n", height);
}

void displayLength(int length)
{
  printf("Room length: %d\n", length);
}

void displayPaintType(char paintType)
{
  printf("Paint Type: %c\n", paintType);
}
