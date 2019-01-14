#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define RND_CTL_BIT_SHIFT   10

// floating point rounding modes: IA-32 Manual, Vol. 1, p. 4-20
typedef enum {
    ROUND_NEAREST_EVEN =    0 << RND_CTL_BIT_SHIFT,
    ROUND_MINUS_INF =       1 << RND_CTL_BIT_SHIFT,
    ROUND_PLUS_INF =        2 << RND_CTL_BIT_SHIFT,
    ROUND_TOWARD_ZERO =     3 << RND_CTL_BIT_SHIFT
} RoundingMode;

// do not change anything above this comment

double roundD(double n, RoundingMode roundingMode)
{
	// here you will set the FPU rounding mode as specified,
	// and then round n to the nearest integer in the specified mode
    
    int nRtn= 0;  
    short rMode;
    short rModeBU;
    short rModeRtn;

    if (roundingMode == 0 << RND_CTL_BIT_SHIFT)
    {
        rMode = 0; // Set rmMde to x00B
    }
    else if (roundingMode == 1 << RND_CTL_BIT_SHIFT)
    {
        rMode = 1024; // Set rmMde to x01B
    }
    else if (roundingMode == 2 << RND_CTL_BIT_SHIFT)
    {
        rMode = 2048; // Set rmMde to x10B
    }
    else if (roundingMode == 3 << RND_CTL_BIT_SHIFT)
    {
        rMode = 3072; // Set rmMde to x11B
    }

    asm volatile(
                 "       fstcw   %2                       \n" // Store CW in rModeBU 
                 "       mov     %2, %%bx                 \n" // Move rModeBU to %bx
                 "       mov     %%bx, %1                 \n" // Move %bx to rModeRtn
                 "       mov     %4, %%ax                 \n" // Move n to %ax
                 "       xor     %%ax, %1                 \n" // XOR %ax and rModeRtn        
                 "       fclex                            \n" // Clear exceptions 
                 "       fldcw   %1                       \n" // Load x87 FPU Control Word
                 "       fldl    %3                       \n" // Load n onto top of FPU 
                 "       frndint                          \n" // Round number in ST(0)
                 "       fist    %0                       \n" // Store value in nRtn 
                 "       fclex                            \n" // Clear exceptions 
                 "       fldcw   %2                       \n" // Load x87 FPU Control Word
                 :       "=m"   (nRtn) , "=m"   (rModeRtn), "=m"    (rModeBU)    // Outputs %0, %1, %2  
                 :       "m"    (n), "m"  (rMode)             // Inputs %2, %3
                 :       "eax", "ebx"                         // Clobbers
    );

    return nRtn;
}

double hullSpeed(double lgth)
{
	// here you will compute the hull speed for the specified boat length,
	// implementing the numerical computation in GNU Assembly Language
	// through use of FPU instructions (do NOT call sqrt() from math.h)

    double lgthOut;    
    double num2 = 1.34; 

    asm volatile(
                 "       fldl    %2                       \n" // Load num2 onto top of FPU 
                 "       fldl    %1                       \n" // Load lgth onto top of FPU 
                 "       fsqrt                            \n" // Sqaure lgth
                 "       fmulp                            \n" // Multiply lgth by num2
                 "       fstpl   %0                       \n" // Store value in lgthOut
                 :       "=m"    (lgthOut)                    // Outputs %0  
                 :       "m"     (lgth), "m"     (num2)       // Inputs %1, %2
                 :       "eax", "ebx", "ecx"                  // Clobbers
    );

    return lgthOut;
}

// do not change anything below this comment, except for printing out your name

double hullSpeedC(double lgth)
{
	// this C implementation of the hull speed computation is provided
	// so you can compare its correct results with the results of your code

	return 1.34 * sqrt(lgth);
}

void printRounded(char *label, RoundingMode roundingMode,
				  double lgth, double hullSpd, double hullSpdC)
{
	printf("%s hullSpeed(%.0f) = %.0f, %.0f\n",
		   label, lgth,
		   roundD(hullSpd,  roundingMode),
		   roundD(hullSpdC, roundingMode));
}

int main (int argc, char **argv)
{
	double	lgth;
	double	hullSpd, hullSpdC;

	printf("CS201 - Assignment 02 - Jaime Landers\n");
	if (argc != 2) {
		printf("need 1 argument: boat length\n");
		return -1;
		}
	lgth = atof(argv[1]);
	hullSpd = hullSpeed(lgth);
	hullSpdC = hullSpeedC(lgth);

	printf("hullSpeed(%.0f) = %.3f, %.3f\n", lgth, hullSpd, hullSpdC);
	printRounded("round even:", ROUND_NEAREST_EVEN, lgth, hullSpd, hullSpdC);
	printRounded("round down:", ROUND_MINUS_INF,    lgth, hullSpd, hullSpdC);
	printRounded("round up:  ", ROUND_PLUS_INF,     lgth, hullSpd, hullSpdC);
	printRounded("round zero:", ROUND_TOWARD_ZERO,  lgth, hullSpd, hullSpdC);

	return 0;
}
