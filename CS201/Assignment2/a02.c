#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// do not change anything above this comment

double hullSpeed(double lgth)
{
	// here you will compute the hull speed for the specified boat length,
	// implementing the numerical computation in GNU Assembly Language
	// through use of FPU instructions (do NOT call sqrt() from math.h)
    printf("\nhullSpeed working \n");

    double lgthOut;    
    double num2 = 1.34; 

    asm volatile(
//  load data into fpu               
                 "       fldl    %2                       \n" // Load num2 onto top of FPU 
                 "       fldl    %1                       \n" // Load lgth onto top of FPU 
//  perform calculation
                 "       fsqrt                            \n" // Sqaure lgth
                 "       fmulp                            \n" // Multiply lgth by num2
//  store data into local variable 
                 "       fstpl   %0                       \n" // Store value in lgthOut
// declarations:
                 :      "=m"    (lgthOut)                     // Outputs  
                 :      "m"     (lgth),     "m" (num2)        // Inputs
                 :      "eax", "ebx", "ecx"                   // Clobbers
    );

//    printf("lgthOut%e\n", lgthOut); //Temp
//    printf("\n"); // Temp

    return lgthOut;
}

// do not change anything below this comment, except for printing out your name

double hullSpeedC(double lgth)
{
	// this C implementation of the hull speed computation is provided
	// so you can compare its correct results with the results of your code

	return 1.34 * sqrt(lgth);
    // Undefined reference
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

	return 0;
}
