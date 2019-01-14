#include "stdio.h"

int main ()
{
    printf("\nWelcome to Object Code Practice\n");

//    int intNumIn = 4;
//    int intNumOut;
//    double dubNumIn = 9.0;
    double dubNumIn = 4.0;
    double dubNumOut;

//    printf("dubNumIn = %e\n", dubNumIn);
//    printf("%d\n", intNumIn);

//    asm(
    asm volatile(
//                 "mov %1,%eax \n\t" 
//                 "mov %eax,%0 \n\t" 
                 "fldl %1   \n"
//                 "fxch      \n"  
//                 "fxch %ST(7)\n"  
//                 "fld %ST(7)\n"
                 "fsqrt     \n"
                 "fstpl %0  \n"
                 : "=m"     (dubNumOut)  
                 : "m"      (dubNumIn)  
//                 : "=m"     (intNumOut) // Outputs  
//                 : "m"      (intNumIn)  // Inputs  
                 : "eax", "ebx", "ecx"  // Clobbers
    ); 

    printf("=====\n");
//    printf("dubNumOut = %e\n", dubNumIn);
    printf("dubNumIn = %e\n", dubNumOut);
//    printf("%d\n", intNumOut);

    return 0;
}

