#include "stdio.h"

int main()
{
    int intNumIn = 1, intNumOut = 0;
    float floatNumIn = 3.5, floatNumOut = 0.0;

//    printf("\nintNumIn = %d\n", intNumIn);
//    printf("\nfloatNumIn = %e\n", floatNumIn);
   
    printf("\nWelcome to Final Prep 1.0\n");

    asm volatile(//"      nop                                 \n" // Do nothing 
                 "      mov     %2, %%eax                \n"
                 "      fld     %3                       \n"
                 "      mov     %%eax, %0                \n"
                 "      fst     %1                       \n"
                 :      "=m" (intNumOut),                       // Output %0 
                        "=m" (floatNumOut)                      // Output %1
                 :      "m" (intNumIn),                         // Inputs %2
                        "m" (floatNumIn)                        // Inputs %3
//                 :      "eax", "ebx", "ecx"                   // Clobbers
    );

    printf("\nintNumOut = %d\n", intNumOut);
    printf("\nfloatNumOut = %e\n\n", floatNumOut);

    return 0;

}
