/*
  program.c
  A room painting invoice calculator. Foundation Progamming Assignment 1
  Kristian Welsh
  date
*/

/* found the ascii code for £ here:
 * http://forums.devshed.com/programming-42/printf-symbol-510114.html
 */
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

void calculateInvoice(int, int, int, char, int, int,
  int *, int *, int *, int *, int *, int *, double *, double *);

int calculateArea(int, int, int);
int calculateMaterialCost(int, char, char);
int calculateUndercoatCost(int, char);
int calculatePaintCost(int, char);
int findPaintPrice(char);
int calculateLabourCost(int);
double calculateVAT(int);

void displayInvoice(char *, int, int, char, int, char,
  int, int, int, int, int, double, double);

void displayTableEdge(void);
void displayTableLine(void);

void displayClientName(char *namePtr);

void displayArea(int);
void displayMaterialsCost(int);
void displayPaintTypeAndPrice(char, int);
void displayUndercoatPrice(char);
void displayPaintCost(int);
void displayUndercoatCost(int);

void displayLabourCost(double);
void displayLabourHours(int);
void displayLabourRate(void);
void displayMinimumLabourCost(void);

void displayPreVATTotal(int);
void displayVATCost(double);

void displayGrandTotal(double);

void displayErrorMessage(void);

/* Gets user input, calculates an invoice, then displays it. */
int main(void) {
  /* Input variables */
  char name[32], paintType, undercoatNeeded;
  int width, height, length, labourHours;
  
  /* Calculation variables */
  int area, materialsCost, paintCost, undercoatCost, labourCost, preVATTotal;
  double VATCost, grandTotal;

  char programHalter;
  askName(name);
  width = askWidth();
  height = askHeight();
  length = askLength();
  paintType = askPaintType();
  undercoatNeeded = askUndercoatNeeded();
  labourHours = askLabour();

  calculateInvoice(width, height, length, paintType,
    undercoatNeeded, labourHours, &area, &paintCost,
    &undercoatCost, &materialsCost, &labourCost,
    &preVATTotal, &VATCost, &grandTotal);

  displayInvoice(name, materialsCost, area, paintType,
    findPaintPrice(paintType), undercoatNeeded, paintCost,
    undercoatCost, labourCost, labourHours, preVATTotal,
    VATCost, grandTotal);

  /* Halt program for user to see output - Later i plan to replace this with a simpler method */
  printf("Press ENTER to exit...");
  scanf("%c", &programHalter);
  return 0;
}

/* Asks the user for the client's name
 * Accepts a pointer to a char array as an argument.
 */
void askName(char *namePtr)
{
  printf("Please enter client name: ");
  gets(namePtr);
  fflush(stdin);
}

/* Asks the user for the width of the room to paint.
 * Returns the entered integer.
 */
int askWidth(void)
{
  int width;
  printf("Please enter room width: ");
  scanf("%d", &width);
  fflush(stdin);
  return width;
}

/* Asks the user for the height of the room to paint.
 * Returns the entered integer.
 */
int askHeight(void)
{
  int height;
  printf("Please enter room height: ");
  scanf("%d", &height);
  fflush(stdin);
  return height;
}

/* Asks the user for the length of the room to paint.
 * Returns the entered integer.
 */
int askLength(void)
{
  int length;
  printf("Please enter room length: ");
  scanf("%d", &length);
  fflush(stdin);
  return length;
}

/* Asks the user for the type of paint to use in the calculation.
 * Returns the entered character.
 */
char askPaintType(void)
{
  char paintType;
  printf("Please enter paint type: ");
  scanf("%c", &paintType);
  fflush(stdin);
  return paintType;
}

/* Asks the user whether an undercoat is needed for the room.
 * Returns the entered character.
 */
int askUndercoatNeeded(void)
{
  char undercoatNeeded;
  printf("Please enter Y if an undercoat is needed, otherwise enter N: ");
  scanf("%c", &undercoatNeeded);
  fflush(stdin);
  return undercoatNeeded;
}

/* Asks the user how many hours of labour is required.
 * Returns the entered integer.
 */
int askLabour(void)
{
  int labourHours;
  printf("Please enter how many hours labour will be needed: ");
  scanf("%d", &labourHours);
  fflush(stdin);
  return labourHours;
}

/* Calculates all invoice information using the user's inputs
 * Accepts all of the user's inputs as arguments.
 * Also accepts pointers to output variables as arguments.
 * Returns each piece of calculated information by
 * changing the values pointed at by pointer arguments.
 */
void calculateInvoice(int width, int height, int length,
  char paintType, int undercoatNeeded, int labourHours,
  int *area, int *paintCost, int *undercoatCost,
  int *materialsCost, int *labourCost, int *preVATTotal,
  double *VATCost, double *grandTotal)
{
  *area = calculateArea(width, height, length);
  *paintCost = calculatePaintCost(*area, paintType);
  *undercoatCost = calculateUndercoatCost(*area, undercoatNeeded);
  *materialsCost = *undercoatCost + *paintCost;

  *labourCost = calculateLabourCost(labourHours);

  *preVATTotal = *paintCost + *labourCost;
  
  *VATCost = calculateVAT(*preVATTotal);
  *grandTotal = *preVATTotal + *VATCost;
}

/* Calculates the area that needs to be painted
 * Accepts the width, height, and length of the room as arguments.
 */
int calculateArea(int width, int height, int length)
{
  int wall1 = width * height;
  int wall2 = length * height;
  int ceiling = width * length;
  return 2 * wall1 + 2 * wall2 + ceiling;
}

/* Calculates the cost of all the materials
 * needed to paint the room.
 * Accepts the room's area, the type of paint
 * needed, and whether an undercoat is needed as arguemnts
 */
int calculateMaterialCost(int area, char paintType, char undercoatNeeded)
{
  int undercoatCost = calculateUndercoatCost(area, undercoatNeeded);
  int paintCost = calculatePaintCost(area, paintType);
  return paintCost + undercoatCost;
}

/* Calculates the cost of any undercoat requested
 * Accepts an area, and a character representing whether
 * an undercoat is needed or not.
 */
int calculateUndercoatCost(int area, char undercoatNeeded)
{
  switch(undercoatNeeded)
  {
    case 'Y':
      return area * UNDERCOAT_PRICE;
    case 'N':
      return 0;
  }
  displayErrorMessage();
  return 0;
}

int calculatePaintCost(int area, char paintType)
{
  return findPaintPrice(paintType) * area;
}

int findPaintPrice(char paintType)
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

void displayInvoice(char *name, int materialsCost, int area,
  char paintType, int paintPrice, char undercoatNeeded,
  int paintCost, int undercoatCost, int labourCost, int labourHours, 
  int preVATTotal, double VATCost, double grandTotal)
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

  displayTableLine();
  displayPreVATTotal(preVATTotal);
  displayVATCost(VATCost);
  displayTableLine();

  displayGrandTotal(grandTotal);

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
  /* i insert the £ with a code for two reasons:
   * 1: using the £ in a string gives you a different
   *    character in the printout
   * 2: i want to be able to set a certain spacing
   *    ammount for it without having a bunch of spaces in the code.
   */
  printf("| Materials Cost: %23c %5d |\n", 156, materialsCost);
}

void displayArea(int area)
{
  printf("| Area to Paint: %16d square meters |\n", area);
}

void displayPaintTypeAndPrice(char paintType, int paintPrice)
{
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

void displayLabourCost(double labourCost)
{
  printf("| Labour Cost: %26c %5.2lf |\n", 156, labourCost);
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

void displayPreVATTotal(int preVATTotal)
{
  printf("| Pre-VAT Total: %24c %5d |\n", 156, preVATTotal);
}

void displayVATCost(double VATCost)
{
  printf("| 20%% VAT: %32c %5.2lf |\n", 156, VATCost);
}

void displayGrandTotal(double grandTotal)
{
  printf("| Grand Total: %26c %5.2lf |\n", 156, grandTotal);
}
