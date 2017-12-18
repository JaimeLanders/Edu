#include "stdio.h"

int main ()
{
    printf("\nWelcome to quiz2!\n\n");

//    long test = 0x0000000000000001;
//    long test = 0x0010000000000000;
//    long test = 0x7FF0000000000001;
//    long test = 0x7FF0000000000000;
//    long test = 0x3FF0000000000000;
//    long test = 0x409E640000000000;

//    printf("test = %e\n", test);

    asm volatile(
                 "    movl    $0x2b,0xffffffdc(%ebp)      \n"
//                 "    movl    $0x31,0xffffffe4(%ebp)      \n"
//                 "    movl    $0x74,0xffffffec(%ebp)      \n"
//                 "    movl    $0x19,0xffffffe8(%ebp)      \n"
//                 "    movl    $0x7,0xffffffd8(%ebp)       \n"
//                 "    movl    $0x14,0xffffffe0(%ebp)      \n"
                 "    mov    $0xdead,%edi		          \n" // Move dead to edi
                 "    mov    $0x2,%ecx	                  \n" // Move 2 to ecx
                 "    mov    %ecx,%esi			          \n" // Move ecx to esi
                 "    mov    $0x3,%ecx			          \n" // Move 3 to ecx
                 "    mov    $0x2,%ebx			          \n" // Move 2 to ebx
                 "    sub    %esi,%ebx			          \n" // Subtract esi from ebx store in ebx
                 "    imul   $0xc,%ebx,%ebx		          \n" // Multiply ebx by 12 store in ebx
                 "    mov    $0x3,%edx			          \n" // Move 3 to edx
                 "    sub    %ecx,%edx			          \n" // Subtract ecx from edx store in edx
//                 "    lea    0xffffffd8(%ebp),%eax	      \n" // Subtract 40 from ebp store in eax 
                 "    lea    (%ebx,%edx,4),%ebx		      \n" // Multiply ebx by 4 add edx store in ebx
                 "    add    %ebx,%eax			          \n" // Add ebx and eax store in eax
                 "    mov    (%eax),%edi		          \n" // Move eax pointer to edi
//                 "    loop   0x4010a9			          \n" // Loop until ecx 0
                 "    mov    %esi,%ecx			          \n" // Move esi to ecx
//                 "    loop   0x4010a2			          \n" // Loop until ecx 0
                 "    mov    $0xbeef,%edi		          \n" // Move beef to edi                
//                 "  fldl     %0                       \n"     
//                 :  "=m"   (test) 
//                 :  "m"   (test) 
    );

//    printf("test = %e\n", test);

    return 0;
}

