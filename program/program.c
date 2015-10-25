/*
  program.c
  A room painting invoice calculator. Foundation Progamming Assignment 1
  Kristian Welsh
  date
*/

/* found the ascii code for £ here: http://forums.devshed.com/programming-42/printf-symbol-510114.html */
#include <stdio.h>
#define UNDERCOAT_PRICE 50
#define LUXURY_PRICE 195
#define STANDARD_PRICE 120
#define ECONOMY_PRICE 65
#define LABOUR_RATE 1500
#define LABOUR_MIN 12000

void askName(char *namePtr);
int askWidth(void);
int askHeight(void);
int askLength(void);
char askPaintType(void);
int askUndercoatNeeded(void);
int askLabour(void);

void calculateInvoice(int, int, int, char, int, int);
int calculateArea(int, int, int);
int calculateMaterialCost(int, char, char);
int calculateUndercoatCost(int, char);
int calculatePaintCost(int, char);
int calculateLabourCost(int);
double calculateVAT(int);
int paintPrice(char);

void displayInvoice(char *, int, int, char, int, char, int);
void displayTableEdge(void);
void displayTableLine(void);
void displayClientName(char *namePtr);
void displayArea(int);
void displayMaterialsCost(double);
void displayPaintTypeAndPrice(char, int);
void displayUndercoat(char);
void displayLabourHours(int);

void displayErrorMessage(void);

int main(void) {
  /* Input variables */
  char name[32], paintType, undercoatNeeded;
  int width, height, length, labourHours;
  
  /* Calculation variables */
  int area, materials;

  char programHalter;
  
  askName(name);
  width = askWidth();
  height = askHeight();
  length = askLength();
  paintType = askPaintType();
  undercoatNeeded = askUndercoatNeeded();
  labourHours = askLabour();

  calculateInvoice(width, height, length, paintType, undercoatNeeded, labourHours);
  /* name, materials cost, area*/
  displayInvoice(name, 1, 1, paintType, paintPrice(paintType), undercoatNeeded, labourHours);

  /* Halt program for user to see output - Later i plan to replace this with a simpler method */
  printf("Press ENTER to exit...");
  scanf("%c", &programHalter);
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

void calculateInvoice(int width, int height, int length, char paintType, int undercoatNeeded, int labourHours)
{
  int preVAT, grandTotal, area, paintCharge, labourCost, valueAddedTax;
  
  area = calculateArea(width, height, length);
  paintCharge = calculateMaterialCost(area, paintType, undercoatNeeded);
  labourCost = calculateLabourCost(labourHours);

  preVAT = paintCharge + labourCost;
  
  valueAddedTax = calculateVAT(preVAT);
  grandTotal = preVAT + valueAddedTax;

  printf("Area: %d\n", area);
  printf("Paint Charge: %d\n", paintCharge);
  printf("Labour Cost: %d\n", labourCost);
  printf("Value Added Tax: %d\n", valueAddedTax);
  printf("Grand Total: %d\n", grandTotal);
}

int calculateArea(int width, int height, int length)
{
  int wall1 = width * height;
  int wall2 = length * height;
  int ceiling = width * length;
  return 2 * wall1 + 2 * wall2 + ceiling;
}

int calculateMaterialCost(int area, char paintType, char undercoatNeeded)
{
  int undercoatCost = calculateUndercoatCost(area, undercoatNeeded);
  int paintCost = calculatePaintCost(area, paintType);
  printf("Undercoat Cost: %d\n", undercoatCost);
  printf("paint Cost: %d\n", paintCost);
  return paintCost + undercoatCost;
}

int calculateUndercoatCost(int area, char undercoatNeeded)
{
  switch(undercoatNeeded)
  {
    case 'Y':
      return area * UNDERCOAT_PRICE;
    case 'N':
      return 0;
    default:
      displayErrorMessage();
      return 0;
  }
  displayErrorMessage();
  return 0;
}

int calculatePaintCost(int area, char paintType)
{
  return paintPrice(paintType) * area;
}

int paintPrice(char paintType)
{
  switch(paintType) {
    case 'L':
      return LUXURY_PRICE;
    case 'S':
      return STANDARD_PRICE;
    case 'E':
      return ECONOMY_PRICE;
  }
  displayErrorMessage();
  return 0;
}

int calculateLabourCost(int labourHours)
{
  int cost = labourHours * LABOUR_RATE;
  if(cost < LABOUR_MIN)
  {
    cost = LABOUR_MIN;
  }
  return cost;
}

double calculateVAT(int total)
{
  return total * 0.2;
}

void displayErrorMessage(void)
{
  puts("something has gone horribly wrong!");
}

void displayInvoice(char *name, int cost, int area, char paintType, int paintPrice, char undercoatNeeded, int labourHours)
{
  displayTableEdge();
  displayClientName(name);
  displayTableLine();
  displayMaterialsCost(cost);
  displayTableLine();
  displayArea(area);
  displayPaintTypeAndPrice(paintType, paintPrice);
  displayUndercoat(undercoatNeeded);
  displayLabourHours(labourHours);
  displayTableEdge();
}

void displayTableEdge(void)
{
  printf("=================================================\n");
}

void displayTableLine(void)
{
  printf("+-----------------------------------------------+\n");
}

void displayClientName(char *namePtr)
{
  printf("| Client Name: %32s |\n", namePtr);
}

void displayMaterialsCost(double cost)
{
  printf("| Materials Cost: %23c %5d |\n", 156, cost);
}

void displayArea(int area)
{
  printf("| Area to Paint: %16d meters square |\n", area);
}

void displayPaintTypeAndPrice(char paintType, int paintPrice)
{
  printf("| Price of Paint Type %c: %28c %4d |\n", paintType, '£', paintPrice);
}

void displayUndercoat(char undercoatNeeded)
{
  printf("| Undercoat Needed: %27c |\n", undercoatNeeded);
}

void displayLabourHours(int labourHours)
{
  printf("| Labour Hours Needed: %24d |\n", labourHours);
}
