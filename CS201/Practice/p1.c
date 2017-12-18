#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned int pFloat = 0x00b00000; 
    float pPointer = *(float*) &pFloat; 
    unsigned int pShift =  *(unsigned int*) &pPointer >> 23; 

    printf("\nWelcome to practice \n");
    printf("\npPointer = 0x%08X", *(unsigned int*) &pPointer);
    printf("\npShift = 0x%08X", *(unsigned int*) &pShift);
    printf("\n");
}
