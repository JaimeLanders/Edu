// do not change this code except in the following ways:
//   * write code for the following functions:
//      * bigOrSmallEndian()
//      * getNextFloat()
//      * printNumberData()
//   * change studentName by changing "I. Forgot" to your actual name

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static char *studentName = "Jaime Landers";

// report whether machine is big or small endian
void bigOrSmallEndian()
{
    unsigned int endInt = 0x12345678;
    char *endChar = (char*) &endInt;

    if (*endChar == 0x78)
        printf("This computer is little-endian");
    else
        printf("This computer is big-endian");

    printf("\n\n");
}

// get next float using scanf()
// returns true (success) or false (failure)
// if call succeeded, return float value via fPtr
bool getNextFloat(float *fPtr)
{
    // replace this code with the call to scanf()
    *fPtr = 0.0;
    float tempFloat = 0.0;

	scanf("%x", (unsigned int*) &tempFloat);

    *fPtr = *(float*) &tempFloat;

	if (fPtr != NULL)
		return true;
    else
        return false;
}

// print requested data for the given number
void printNumberData(float f)
{
	// replace this call to printf with your actual code
    int signBit = 0;
    int expBits = 0;
    int fractBits = 0;
    int fractSig = 0;
    int trueExp = 0;

    signBit = *(unsigned int*) &f >> 31;   
    expBits = *(unsigned int*) &f & 0x7f800000;   
    expBits >>= 23;   
    fractBits = *(unsigned int*) &f & 0x007fffff;   
    fractSig = fractBits >> 22;

    if (expBits != 0)
        trueExp = expBits - 127;
    else 
        trueExp = expBits - 126;

    printf("0x%08X", *(unsigned int*) &f);
    printf("\nsignBit %u", signBit);
    printf(", ");
    printf("expBits %u", expBits);
    printf(", ");
    printf("fractBits 0x%08X", fractBits);
    printf("\n");

    if (expBits != 0 && expBits != 255 && fractBits != 0)
        printf("normalized: exp = %d", trueExp);
    else if (expBits == 0 && expBits != 255 && fractBits != 0)
        printf("denormalized: exp = %d", trueExp);
    else if (signBit == 0 && expBits == 255 && fractBits == 0)
        printf("+infinity");
    else if (signBit == 1 && expBits == 255 && fractBits == 0)
        printf("-infinity");
    else if (expBits == 255 && fractSig == 1)
        printf("QNaN");
    else if (expBits == 255 && fractSig == 0)
        printf("SNaN");
    else if (signBit == 0 && expBits == 0  && fractBits == 0)
        printf("+zero");
    else if (signBit == 1 && expBits == 0  && fractBits == 0)
        printf("-zero");
    printf("\n\n");
}

// do not change this function in any way
int main(int argc, char **argv)
{
	float	f;								// number currently being analyzed
	bool	validInput;						// was user input valid?

	printf("CS201 - A01 - %s\n\n", studentName);
	bigOrSmallEndian();
	for (;;) {
		if (argc == 1)						// allow grading script to control ...
			printf("> ");					// ... whether prompt character is printed
		validInput = getNextFloat(&f);
		if (! validInput) {					// encountered bad input
			printf("bad input\n");
			while (getchar() != '\n') ;		// flush bad line from input buffer
			continue;
			}
		printNumberData(f);
		if (f == 0.0) {
			printf("bye...\n");
			break;
			}
		}
	printf("\n");
	return 0;
}
