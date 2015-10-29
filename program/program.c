/* program.c
	A room painting invoice calculator. Foundation Progamming Assignment 1
	Kristian Welsh
	27/10/2015
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
double askHeight(void);
double askWidth(void);
double askLength(void);
char askPaintType(void);
char askUndercoatNeeded(void);
double askLabour(void);
void tellUserTheirWallsAreTooBigIfTheyAre(double);
void tellUserTheirWallsAreTooHighIfTheyAre(double);
int inputWhithinBounds(double, double, double);
int isValidPaintType(char);
int isValidUndercoatCharacter(char);
void tellUserToOnlyUseValidPaintTypesIfTheyHaveNot(char);
void tellTheUserTheyEnteredAWrongCharacterIfTheyHave(char);

void calculateInvoice(double, double, double, char, char, double,
	double *, double *, double *, double *, double *, double *, double *, double *);

double calculateArea(double, double, double);
double calculateMaterialCost(double, char, char);
double calculateUndercoatCost(double, char);
double calculatePaintCost(double, char);
int findPaintPrice(char);
double calculateLabourCost(double);
double calculateVAT(double);

void displayInvoice(char *, double, double, char, double, char,
	double, double, double, double, double, double, double);

void displayTableEdge(void);
void displayTableLine(void);

void displayClientName(char *);

void displayArea(double);
void displayMaterialsCost(double);
void displayPaintTypeAndPrice(char, double);
void displayUndercoatPrice(char);
void displayPaintCost(double);
void displayUndercoatCost(double);

void displayLabourCost(double);
void displayLabourHours(double);
void displayLabourRate(void);
void displayMinimumLabourCost(void);

void displayPreVATTotal(double);
void displayVATCost(double);

void displayGrandTotal(double);

void displayErrorMessage(void);

/* Gets user input, calculates an invoice, then displays it. */
int main(void)
{
	/* Input variables */
	char name[32], paintType, undercoatNeeded;
	double height, width, length, labourHours;
	
	/* Calculation variables */
	double area, materialsCost, paintCost, undercoatCost, labourCost, preVATTotal;
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

	/* Halt program for user to see output */
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
  scanf("%31[^\n]", namePtr);
	fflush(stdin);
}

/* Asks the user for the height of the room to paint.
 * Returns the entered integer once valid.
 */
double askHeight(void)
{
	double height;
	do
	{
		printf("Please enter room height in meters: ");
		scanf("%lf", &height);
		fflush(stdin);
		tellUserTheirWallsAreTooHighIfTheyAre(height);
	} while(!inputWhithinBounds(height, 2, 6));
	return height;
}

/* Asks the user for the width of the room to paint.
 * Returns the entered integer once valid.
 */
double askWidth(void)
{
	double width;
	do
	{
		printf("Please enter room width in meters: ");
		scanf("%lf", &width);
		fflush(stdin);
		tellUserTheirWallsAreTooBigIfTheyAre(width);
	} while(!inputWhithinBounds(width, 1, 25));
	return width;
}

/* Asks the user for the length of the room to paint.
 * Returns the entered integer once valid.
 */
double askLength(void)
{
	double length;
	do
	{
		printf("Please enter room length in meters: ");
		scanf("%lf", &length);
		fflush(stdin);
		tellUserTheirWallsAreTooBigIfTheyAre(length);
	} while(!inputWhithinBounds(length, 1, 25));
	return length;
}

/* Asks the user for the type of paint to use in the calculation.
 * Returns the entered character once valid.
 */
char askPaintType(void)
{
	char paintType;
	printf("\n");
	printf("Enter L for luxury paint at %c1.95 per square meter\n", 156);
	printf("Enter S for standard paint at %c1.20 per square meter\n", 156);
	printf("Enter E for economy paint at %c0.65 per square meter\n", 156);
	do
	{
		printf("Paint Type: ");
		scanf("%c", &paintType);
		fflush(stdin);
		tellUserToOnlyUseValidPaintTypesIfTheyHaveNot(paintType);
	} while(!isValidPaintType(paintType));
	return paintType;
}

/* Asks the user whether an undercoat is needed for the room.
 * Returns the entered character once valid.
 */
char askUndercoatNeeded(void)
{
	char undercoatNeeded;
	printf("\n");
	printf("Undercoat paint costs %c0.50 per square meter.\n", 156);
	puts("If the room requires an undercoat enter Y otherwise enter N.");
	do
	{
		printf("Undercoat Required: ");
		scanf("%c", &undercoatNeeded);
		fflush(stdin);
		tellTheUserTheyEnteredAWrongCharacterIfTheyHave(undercoatNeeded);
	} while(!isValidUndercoatCharacter(undercoatNeeded));
	return undercoatNeeded;
}

/* Asks the user how many hours of labour is required.
 * Returns the entered integer.
 */
double askLabour(void)
{
	double labourHours;
	printf("\n");
	printf("Please enter how many hours labour will be needed: ");
	scanf("%lf", &labourHours);
	fflush(stdin);
	return labourHours;
}

/* Tells the user if their walls are too tall or short. */
void tellUserTheirWallsAreTooHighIfTheyAre(double height)
{
	if(!inputWhithinBounds(height, 2, 6))
	{
		puts("\nThis program only works for rooms between 2 and 6 meters tall.");
	}
}

/* If the wall size is too large, inform the user */
void tellUserTheirWallsAreTooBigIfTheyAre(double wallSize)
{
	if(!inputWhithinBounds(wallSize, 1, 25))
	{
		puts("\nThis program only works for walls between 1 and 25 meters.");
	}
}

/* If the user enters a nonexistant paint type, tell them. */
void tellUserToOnlyUseValidPaintTypesIfTheyHaveNot(char paintType)
{
	if(!isValidPaintType(paintType))
	{
		puts("\nYou have entered invalid data, please enter either L S or E.");
	}
}

/* If the user enters an unvalid undercoat character, tell them */
void tellTheUserTheyEnteredAWrongCharacterIfTheyHave(char undercoatNeeded)
{
	if(!isValidUndercoatCharacter(undercoatNeeded))
	{
		puts("\nYou have entered invalid data, please enter Y or N.");
	}
}

/* returns 1 if the unput is between the upper and lower bounds
 * otherwise returns 0.
 */
int inputWhithinBounds(double input, double min, double max)
{
	int result = ((min <= input) && (input <= max));
	return result;
}

/* Returns 1 if the paintType is valid
 * Otherwise returns 0.
 */
int isValidPaintType(char paintType)
{
	switch(paintType)
	{
		case 'S':
		case 'E':
		case 'L':
			return 1;
	}
	return 0;
}

/* Returns 1 if underchatNeeded is valid
 * Otherwise returns 0.
 */
int isValidUndercoatCharacter(char undercoatNeeded)
{
	switch(undercoatNeeded)
	{
		case 'Y':
		case 'N':
			return 1;
	}
	return 0;
}

/* Calculates all invoice information using the user's inputs
 * Accepts all of the user's inputs as arguments.
 * Also accepts pointers to output variables as arguments.
 * Returns each piece of calculated information by
 * changing the values pointed at by pointer arguments.
void calculateInvoice(double, double, double, char, double, double,
 */
void calculateInvoice(double width, double height, double length,
	char paintType, char undercoatNeeded, double labourHours,
	double *area, double *paintCost, double *undercoatCost,
	double *materialsCost, double *labourCost, double *preVATTotal,
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
double calculateArea(double width, double height, double length)
{
	double wall1 = width * height;
	double wall2 = length * height;
	double ceiling = width * length;
	return 2 * wall1 + 2 * wall2 + ceiling;
}

/* Calculates the cost of all the materials
 * needed to paint the room.
 * Accepts the room's area, the type of paint
 * needed, and whether an undercoat is needed as arguemnts
 */
double calculateMaterialCost(double area, char paintType, char undercoatNeeded)
{
	double undercoatCost = calculateUndercoatCost(area, undercoatNeeded);
	double paintCost = calculatePaintCost(area, paintType);
	return paintCost + undercoatCost;
}

/* Calculates the cost of any undercoat requested
 * Accepts an area, and a character representing whether
 * an undercoat is needed or not.
 */
double calculateUndercoatCost(double area, char undercoatNeeded)
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
double calculatePaintCost(double area, char paintType)
{
	return findPaintPrice(paintType) * area;
}

/* Finds the price of the paintType provided
 * Accepts a character representing the type of paint required.
 */
int findPaintPrice(char paintType)
{
	switch(paintType)
	{
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
double calculateLabourCost(double labourHours)
{
	double cost = labourHours * LABOUR_RATE;
	if(cost < LABOUR_MIN)
	{
		cost = LABOUR_MIN;
	}
	return cost;
}

/* Calculates how much VAT is due to be paid */
double calculateVAT(double total)
{
	return total * 0.2;
}

/* Displays an error message.
 * Hopefully the user never sees this, as this means there's an error in my code.
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
void displayInvoice(char *name, double materialsCost, double area,
	char paintType, double paintPrice, char undercoatNeeded,
	double paintCost, double undercoatCost, double labourCost, double labourHours, 
	double preVATTotal, double VATCost, double grandTotal)
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
void displayArea(double area)
{
	printf("| Area to Paint: %16.2lf square meters |\n", area);
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
	double price;
	if(undercoatNeeded == 'Y')
	{
    price = UNDERCOAT_PRICE;
	}
	else
	{
    price = 0;
	}
	printf("| Price of Undercoat: %18c %6.2lf |\n", 156, price / 100);
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
	 *		character in the printout
	 * 2: i want to be able to set a certain spacing
	 *		ammount for it without having a bunch of spaces in the code.
	 */
	printf("| Materials Cost: %22c %6.2lf |\n", 156, materialsCost / 100);
}

/* Displays the number of hours the job is estimated to take */
void displayLabourHours(double labourHours)
{
	printf("| Labour Hours Needed: %24.2lf |\n", labourHours);
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
	printf("| Grand Total: %25c %6.2lf |\n", 156, grandTotal / 100);
}

