#include <stdio.h>
#include <stdlib.h>

// You are only allowed to make changes to this code as specified by the comments in it.

// The code you submit must have these two values.
#define N_TIMES		600000
#define ARRAY_SIZE	 10000

int main(void)
{
	double  *array = calloc(ARRAY_SIZE, sizeof(double));
	int		i;

	// You can add variables between this comment ...
    double  *ptr; 
	double  tSum = 0;
	double  sum = 0, sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;// = 0;
//	double  sum = 0;
//	double  sum1 = 0;
//	double  sum2 = 0;
//	double  sum3 = 0;
//	double  sum4 = 0;
    long long num1 = 0; // Temp
    long long num2 = 0; // Temp
	// ... and this one.

	// Please change 'your name' to your actual name.
	printf("CS201 - Asgmt 4 - Jaime Landers\n");

	for (i = 0; i < N_TIMES; i++) {

		// You can change anything between this comment ...

//		int j;
		int k; // Temp

       	for (k = 0; k < ARRAY_SIZE; k++) { // 21.8 Seconds
    	    tSum += array[k];
            num1++;
		}

/*       	for (j = 0; j < ARRAY_SIZE; j++) { // 21.8 Seconds
    	    sum += array[j];
            num2++;
		}
*/
/*       	for (ptr = array; ptr < &array[ARRAY_SIZE] ; ptr++) { // 20.66 Seconds
    	    sum += *ptr; 
		}
*/
/*       	for (j = 0; j < ARRAY_SIZE; j += 4) { // 20.37 Seconds
    	    sum += array[j] ;
    	    sum += array[j+1];
    	    sum += array[j+2];
    	    sum += array[j+3];
		}
*/
/*       	for (ptr = array; ptr < &array[ARRAY_SIZE]; ptr += 4) { // 20.33 Seconds
    	    sum += *ptr; 
    	    sum += *ptr + 1; 
    	    sum += *ptr + 2; 
    	    sum += *ptr + 3; 
		}
*/
/*       	for (ptr = array; ptr < &array[ARRAY_SIZE]; ptr += 3) { // 13.63 Seconds
    	    sum1 += *ptr; 
    	    sum2 += *ptr + 1; 
    	    sum2 += *ptr + 2; 
		}
        sum = sum1 + sum2;
*/
/*       	for (j = 0; j < ARRAY_SIZE; j += 2) { // 10.89 Seconds
    	    sum1 += array[j];
    	    sum2 += array[j+1];
		}
        sum = sum1 + sum2;
*/
/*       	for (j = 0; j < ARRAY_SIZE; j += 2) { // 10.53 Seconds
    	    sum += array[j] + array[j+1];
		}
*/
/*       	for (ptr = array; ptr < &array[ARRAY_SIZE]; ptr += 2) { // 10.41 Seconds
    	    sum1 += *ptr; 
    	    sum2 += *ptr + 1; 
		}
        sum = sum1 + sum2;
*/
/*       	for (ptr = array; ptr < &array[ARRAY_SIZE]; ptr += 8) { // 10.27 Seconds
    	    sum1 += *ptr; 
    	    sum1 += *ptr + 1; 
    	    sum1 += *ptr + 2; 
    	    sum1 += *ptr + 3; 
    	    sum2 += *ptr + 4; 
    	    sum2 += *ptr + 5; 
    	    sum2 += *ptr + 6; 
    	    sum2 += *ptr + 7; 
		}
        sum = sum1 + sum2;
*/
/*       	for (ptr = array; ptr < &array[ARRAY_SIZE]; ptr += 4) { // 10.26 Seconds
    	    sum1 += *ptr; 
    	    sum1 += *ptr + 1; 
    	    sum2 += *ptr + 2; 
    	    sum2 += *ptr + 3; 
		}
        sum = sum1 + sum2;
*/
/*       	for (ptr = array; ptr < &array[ARRAY_SIZE]; ptr += 4) { // 10.24 Seconds
    	    sum += *ptr; 
    	    sum += *ptr + 1; 
    	    sum1 += *ptr + 2; 
    	    sum1 += *ptr + 3; 
		}
        sum += sum1;
*/
/*       	for (ptr = array; ptr < &array[ARRAY_SIZE]; ptr += 4) { // 7.26 Seconds
    	    sum1 += *ptr;
    	    sum2 += *ptr+1;
    	    sum3 += *ptr+2;
    	    sum4 += *ptr+3;
//            num2 += 4;
		}  // Close inner loop
*/
/*       	for (ptr = array; ptr < &array[ARRAY_SIZE]; ptr += 4) { // 5.83 Seconds
    	    sum += *ptr + *ptr+1; 
    	    sum1 += *ptr+2 + *ptr+3; 
//            num2 += 4;
		}
        sum += sum1;
*/
/*      	for (ptr = array; ptr < &array[ARRAY_SIZE]; ptr += 12 ) { // 5.76 Seconds
    	    sum += *ptr + *ptr+1; 
    	    sum += *ptr+2 + *ptr+3; 
    	    sum += *ptr+4 + *ptr+5; 
    	    sum1 += *ptr+6 + *ptr+7; 
    	    sum1 += *ptr+8 + *ptr+9; 
    	    sum1 += *ptr+10 + *ptr+11; 
//            num2 += 4;
		}
        sum += sum1;
*/
/*       	for (ptr = array; ptr < &array[ARRAY_SIZE]; ptr += 8) { // 5.71 Seconds
    	    sum += *ptr + *ptr+1; 
    	    sum += *ptr+2 + *ptr+3; 
    	    sum1 += *ptr+4 + *ptr+5; 
    	    sum1 += *ptr+6 + *ptr+7; 
//            num2 += 4;
		}  // Close inner loop
*/
/*       	for (ptr = array; ptr < &array[ARRAY_SIZE]; ptr += 8) { // 5.59 Seconds
    	    sum1 += *ptr + *ptr+1; 
    	    sum2 += *ptr+2 + *ptr+3; 
    	    sum3 += *ptr+4 + *ptr+5; 
    	    sum4 += *ptr+6 + *ptr+7; 
//            num2 += 4;
		}  // Close inner loop
*/
       	for (ptr = array; ptr < &array[ARRAY_SIZE]; ptr += 8) { // 4.84 Seconds
    	    sum1 += *ptr + *(ptr+1); 
    	    sum2 += *(ptr+2) + *(ptr+3); 
    	    sum3 += *(ptr+4) + *(ptr+5); 
    	    sum4 += *(ptr+6) + *(ptr+7); 
            num2 += 8;
		}  // Close inner loop

		// ... and this one. But your inner loop must do the same
		// number of additions as this one does.

	}  // Close outer loop

	// You can add some final code between this comment ...
    sum = sum1 + sum2 + sum3 + sum4;
//    sum += sum1;
    printf("\nsum = %e\n", sum); // Temp
    printf("\ntSum = %e\n", tSum); // Temp
    printf("\nnum1 = %lld\n", num1); // Temp
    printf("\nnum2 = %lld\n", num2); // Temp
	// ... and this one.

	return 0;
}
