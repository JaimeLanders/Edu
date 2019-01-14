#include "stdio.h"

int main (int argc, char * argv[])
{
    printf ("\nWelcome to Midterm Practice!\n");

    if (argc < 2)
    {
        printf("Please enter an argument...\n\n");
        return 0;
    }
    else
    {
        printf("Argument = %s\n", argv[1]);

        int intNum;
        float floatNum; 
        int hexNum; 
        char cString[100]; 

        printf("Enter an integer: ");
        scanf("%i", &intNum);
        printf("Integer: %i\n", intNum);

        printf("Enter a float: ");
        scanf("%e", &floatNum);
        printf("Float: %e\n", floatNum);
    
        printf("Enter a hex: ");
        scanf("%x", &hexNum);
        printf("Hex: 0x%x\n", hexNum);

        printf("Enter a string: ");
        scanf("%s", cString);
        printf("String: %s\n", cString);

        return 0;
    }
}
