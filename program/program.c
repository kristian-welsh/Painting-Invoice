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

/* Prototype declarations.
 * Fun fact: there are more than 30 of these
 * yes, i do enjoy typing :)
 */
void askName(char *namePtr);
int askHeight(void);
int askWidth(void);
int askLength(void);
char askPaintType(void);
int askUndercoatNeeded(void);
int askLabour(void);
void tellUserTheirWallsAreTooBigIfTheyAre(int);
void tellUserTheirWallsAreTooHighIfTheyAre(int);
int inputWhithinBounds(int, int, int);

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

void displayClientName(char *);

void displayArea(int);
void displayMaterialsCost(double);
void displayPaintTypeAndPrice(char, double);
void displayUndercoatPrice(char);
void displayPaintCost(double);
void displayUndercoatCost(double);

void displayLabourCost(double);
void displayLabourHours(int);
void displayLabourRate(void);
void displayMinimumLabourCost(void);

void displayPreVATTotal(double);
void displayVATCost(double);

void displayGrandTotal(double);

void displayErrorMessage(void);

/* Gets user input, calculates an invoice, then displays it. */
int main(void) {
  /* Input variables */
  char name[32], paintType, undercoatNeeded;
  int height, width, length, labourHours;
  
  /* Calculation variables */
  int area, materialsCost, paintCost, undercoatCost, labourCost, preVATTotal;
  double VATCost, grandTotal;

  /* I use this to stop the program so the data is shown */
  char programHalter;

  askName(name);
  height = askHeight();
  width = askWidth();
  length = askLength();
  paintType = askPaintType();
  undercoatNeeded = askUndercoatNeeded();
  labourHours = askLabour();

  system("cls");

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
  printf("Please enter client name (max 32 digits): ");
  gets(namePtr);
  fflush(stdin);
}

/* Asks the user for the height of the room to paint.
 * Returns the entered integer.
 */
int askHeight(void)
{
  int height;
  do {
    printf("Please enter room height: ");
    scanf("%d", &height);
    fflush(stdin);
    tellUserTheirWallsAreTooHighIfTheyAre(height);
  } while(!inputWhithinBounds(height, 2, 6));
  return height;
}

/* Asks the user for the width of the room to paint.
 * Returns the entered integer.
 */
int askWidth(void)
{
  int width;
  do {
    printf("Please enter room width in meters: ");
    scanf("%d", &width);
    fflush(stdin);
    tellUserTheirWallsAreTooBigIfTheyAre(width);
  } while(!inputWhithinBounds(width, 5, 25));
  return width;
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

/* Tells the user if their walls are too tall or short. */
void tellUserTheirWallsAreTooHighIfTheyAre(int height)
{
  if(!inputWhithinBounds(height, 2, 6))
  {
    puts("This program only works for rooms between 2 and 6 meters tall.");
  }
}

/* If the wall size is too large, inform the user */
void tellUserTheirWallsAreTooBigIfTheyAre(int wallSize)
{
  if(!inputWhithinBounds(wallSize, 5, 25))
  {
    puts("This program only works for walls between 5 and 25 meters.");
  }
}

/* returns 1 if the unput is between the upper and lower bounds
 * otherwise returns 0.
 */
int inputWhithinBounds(int input, int min, int max)
{
  int result = ((min <= input) && (input <= max));
  return result;
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

/* Calculates the cost of paint type requested
 * Accepts an area, and a character representing the
 * type of paint required.
 */
int calculatePaintCost(int area, char paintType)
{
  return findPaintPrice(paintType) * area;
}

/* Finds the price of the paintType provided
 * Accepts a character representing the type of paint required.
 */
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

/* Calculates the cost of the labour required
 * Accepts the number of hours of labour needed
 * returns the rate * the hours or the minimum,
 * Whichever is higher
 */
int calculateLabourCost(int labourHours)
{
  int cost = labourHours * LABOUR_RATE;
  if(cost < LABOUR_MIN)
  {
    cost = LABOUR_MIN;
  }
  return cost;
}

/* Calculates how much VAT is due to be paid */
double calculateVAT(int total)
{
  return total * 0.2;
}

/* Displays an error message.
 * Hopefully the user never sees this.
 */
void displayErrorMessage(void)
{
  puts("something has gone horribly wrong!");
}

/* Displays the invoice
 * Accepts a whole host of variables that encompases
 * almost all the information gathered thus far.
 * Arguments that represent currency are accepted as integers in
 * pennies, and cast to doubles when passed to the indevidual
 * display functions for proper formatting to the user.
 */
void displayInvoice(char *name, int materialsCost, int area,
  char paintType, int paintPrice, char undercoatNeeded,
  int paintCost, int undercoatCost, int labourCost, int labourHours, 
  int preVATTotal, double VATCost, double grandTotal)
{
  displayTableEdge();
  displayClientName(name);
  displayTableLine();

  displayArea(area);
  displayPaintTypeAndPrice(paintType, paintPrice);
  displayUndercoatPrice(undercoatNeeded);
  displayPaintCost(paintCost);
  displayUndercoatCost(undercoatCost);

  displayTableLine();
  displayMaterialsCost(materialsCost);
  displayTableLine();

  displayLabourHours(labourHours);
  displayLabourRate();
  displayMinimumLabourCost();

  displayTableLine();
  displayLabourCost(labourCost);
  displayTableLine();

  displayPreVATTotal(preVATTotal);
  displayVATCost(VATCost);

  displayTableLine();
  displayGrandTotal(grandTotal);
  displayTableEdge();
}

/* Displays a table edge */
void displayTableEdge(void)
{
  printf("=================================================\n");
}

/* Displays a table divide */
void displayTableLine(void)
{
  printf("+-----------------------------------------------+\n");
}

/* Displays the client name */
void displayClientName(char *namePtr)
{
  printf("| Client Name: %32s |\n", namePtr);
}

/* Displays the area to be painted */
void displayArea(int area)
{
  printf("| Area to Paint: %16d square meters |\n", area);
}

/* Displays the paint type and the price of that paint type */
void displayPaintTypeAndPrice(char paintType, double paintPrice)
{
  printf("| Price of Paint Type %c: %15c %6.2lf |\n",
    paintType, 156, paintPrice / 100);
}

/* Displays whether an undercoat was requested, and it's price */
void displayUndercoatPrice(char undercoatNeeded)
{
  double price = UNDERCOAT_PRICE;
  if(undercoatNeeded == 'Y')
  {
    printf("| Price of Undercoat: %19c %6.2lf |\n", 156, price / 100);
  }
  else
  {
    printf("| Price of Undercoat: %18c %6.2lf |\n", 156, 0);
  }
}

/* Displays the cost of all paint to be used */
void displayPaintCost(double paintCost)
{
  printf("| Cost of Main Paint: %18c %6.2lf |\n", 156, paintCost / 100);
}

/* Displays the cost of all the undercoat paint used */
void displayUndercoatCost(double undercoatCost)
{
  printf("| Cost of Undercoat: %19c %6.2lf |\n", 156, undercoatCost / 100);
}

/* Display the materials cost */
void displayMaterialsCost(double materialsCost)
{
  /* i insert the £ with a code for two reasons:
   * 1: using the £ in a string gives you a "á"
   *    character in the printout
   * 2: i want to be able to set a certain spacing
   *    ammount for it without having a bunch of spaces in the code.
   */
  printf("| Materials Cost: %22c %6.2lf |\n", 156, materialsCost);
}

/* Displays the number of hours the job is estimated to take */
void displayLabourHours(int labourHours)
{
  printf("| Labour Hours Needed: %24d |\n", labourHours);
}

/* Displays the pay rate of the labourer */
void displayLabourRate(void)
{
  double rate = LABOUR_RATE;
  printf("| Labour Rate: %25c %6.2lf |\n", 156, rate / 100);
}

/* Displays the minimum the labourer will accept for a job */
void displayMinimumLabourCost(void)
{
  double min = LABOUR_MIN;
  printf("| Minimum Labour Cost: %17c %6.2lf |\n", 156, min / 100);
}

/* Displays the cost of the labour used */
void displayLabourCost(double labourCost)
{
  printf("| Labour Cost: %25c %6.2lf |\n", 156, labourCost / 100);
}

/* Dipslays the sum of all costs before VAT is added */
void displayPreVATTotal(double preVATTotal)
{
  printf("| Pre-VAT Total: %23c %6.2lf |\n", 156, preVATTotal / 100);
}

/* Displays the ammmount of VAT to be added */
void displayVATCost(double VATCost)
{
  printf("| 20%% VAT: %29c %6.2lf |\n", 156, VATCost / 100);
}
/* Displays the final total with the VAT included */
void displayGrandTotal(double grandTotal)
{
  printf("| Grand Total: %25c %6.2lf |\n", 156, grandTotal/100);
}
