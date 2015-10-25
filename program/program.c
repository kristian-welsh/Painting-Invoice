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

void displayInvoice(char *, int, int, char, int, char, int, int, int, int);
void displayTableEdge(void);
void displayTableLine(void);
void displayClientName(char *namePtr);
void displayArea(int);
void displayMaterialsCost(int);
void displayPaintTypeAndPrice(char, int);
void displayUndercoatPrice(char);
void displayPaintCost(int);
void displayUndercoatCost(int);
void displayLabourCost(int);
void displayLabourHours(int);
void displayLabourRate(void);
void displayMinimumLabourCost(void);

void displayErrorMessage(void);

int main(void) {
  /* Input variables */
  char name[32], paintType, undercoatNeeded;
  int width, height, length, labourHours;
  
  /* Calculation variables */
  int area, materialsCost, paintCost, undercoatCost, labourCost;

  char programHalter;
  
  askName(name);
  width = askWidth();
  height = askHeight();
  length = askLength();
  paintType = askPaintType();
  undercoatNeeded = askUndercoatNeeded();
  labourHours = askLabour();

  calculateInvoice(width, height, length, paintType, undercoatNeeded, labourHours);
  area = 69;
  materialsCost = 69;
  paintCost = 69;
  undercoatCost = 69;
  labourCost = 69;

  /* name, materials cost, area*/
  displayInvoice(name, area, materialsCost, paintType, paintPrice(paintType), undercoatNeeded, paintCost, undercoatCost, labourCost, labourHours);

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

void displayInvoice(char *name, int materialsCost, int area, char paintType, int paintPrice, char undercoatNeeded, int paintCost, int undercoatCost, int labourCost, int labourHours)
{
  displayTableEdge();
  displayClientName(name);

  displayTableLine();
  displayMaterialsCost(materialsCost);
  displayTableLine();

  displayArea(area);
  displayPaintTypeAndPrice(paintType, paintPrice);
  displayUndercoatPrice(undercoatNeeded);
  displayPaintCost(paintCost);
  displayUndercoatCost(undercoatCost);

  displayTableLine();
  displayLabourCost(labourCost);
  displayTableLine();

  displayLabourHours(labourHours);
  displayLabourRate();
  displayMinimumLabourCost();
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

void displayMaterialsCost(int materialsCost)
{
  printf("| Materials Cost: %23c %5d |\n", 156, materialsCost);
}

void displayArea(int area)
{
  printf("| Area to Paint: %16d square meters |\n", area);
}

void displayPaintTypeAndPrice(char paintType, int paintPrice)
{
  /* i insert the £ with a code for two reasons:
   * 1: using the £ in a string gives you a different character in the printout
   * 2: i want to be able to set a certain spacing ammount for it withous having a bunch of spaces in the code.
   */
  printf("| Price of Paint Type %c: %16c %5d |\n", paintType, 156, paintPrice);
}

void displayUndercoatPrice(char undercoatNeeded)
{
  if(undercoatNeeded == 'Y')
  {
    printf("| Price of Undercoat: %19c %5d |\n", 156, UNDERCOAT_PRICE);
  }
  else
  {
    printf("| Price of Undercoat: %19c %5d |\n", 156, 0);
  }
}

void displayPaintCost(int paintCost)
{
  printf("| Cost of Main Paint: %19c %5d |\n", 156, paintCost);
}

void displayUndercoatCost(int undercoatCost)
{
  printf("| Cost of Undercoat: %20c %5d |\n", 156, undercoatCost);
}

void displayLabourCost(int labourCost)
{
  printf("| Labour Cost: %26c %5d |\n", 156, labourCost);
}

void displayLabourHours(int labourHours)
{
  printf("| Labour Hours Needed: %24d |\n", labourHours);
}

void displayLabourRate(void)
{
  printf("| Labour Rate: %26c %5d |\n", 156, LABOUR_RATE);
}

void displayMinimumLabourCost(void)
{
  printf("| Minimum Labour Cost: %18c %5d |\n", 156, LABOUR_MIN);
}
