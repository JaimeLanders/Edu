// demo of GCC inline assembler

char	charArray[] =	{0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
						 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F};
int		intArray[] =	{10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

int main(int argc, char **argv)
{
	int		localVar =	0x12345678;
	double	fpVar =		16.0;

	// Embedded Assembly Language:
	asm("		Inst	Source, Destination			\n" // Comments & Details
		// IA-32 Intructions:
		// Move:
		"		movS Src, Dest						\n" // Dest = Src
		"		movsbS Src,Dest						\n" // Dest (long) = Src (byte), sign extend
		"		leaS Src, Dest						\n" // Dest = address of Src
		// Arithmetic:
		"		addS Src, Dest						\n" // Dest = Dest + Src
		"		subS Src, Dest						\n" // Dest = Dest - Src
		"		imulS Src, Dest						\n" // Dest = Dest * Src
		"		idivS Src, Dest						\n" // Dest = Dest / Src		
		"		incS Dest							\n" // Dest = Dest + 1
		"		decS Dest							\n" // Dest = Dest - 1
		"		negS Dest							\n" // Dest = – Dest	
		// Shift:
		"		salS k Src, Dest					\n" // Dest = Dest << Src k bits
		"		sarS k Src, Dest					\n" // Dest = Dest >> Src arithmetic shift k bits
		"		shlS k Src, Dest					\n" // Dest = Dest << Src logical shift	k bits
		"		shrS k Src, Dest					\n" // Dest = Dest >> Src logical shift	k bits
		// Logic:
		"		andS Src, Dest						\n" // Dest = Dest & Src
		"		orS Src, Dest						\n" // Dest = Dest | Src		
		"		xorS Src, Dest						\n" // Dest = Dest ^ Src
		"		notS Dest							\n" // Dest = ~ Dest
		// Flow:
		"		cmpS Src2, Src1						\n" // Compare Src2 and Src1, Sets CCs Src1 – Src2
		"		testS Src2, Src1					\n" // And Src1 and Src2, Sets CCs Src1 & Src2
		"		jmp label							\n" // jump uncoditionally to label
		"		je label							\n" // jump if equal (ZF on)
		"		jz label							\n" // jump if zero	
		"		jne label							\n" // jump not equal (ZF off)
		"		jnz label							\n" // jump if not zero	
		"		js label							\n" // jump negative
		"		jns label							\n" // jump non-negative	
		// Signed Comparisons
		"		jg label							\n" // jump greater (signed) (!(SF xor OF))
		"		jge label							\n" // jump greater or equal (signed) (!(SF xor OF) and !ZF)
		"		jl label							\n" // jump less (signed) (SF xor OF)
		"		jle label							\n" // jump less or equal (signed) ((SF xor OF) or ZF) 
		// Unsigned Comparisons
		"		ja label							\n" // jump above (unsigned) (ZF off and CF off)
		"		jae label							\n" // jump above (unsigned) (CF off)
		"		jb label							\n" // jump jump below (unsigned) (CF on)		
		"		jbe label							\n" // jump jump below (unsigned) (ZF on or CF on)		
		// Stack:
		"		pushS Src							\n" // %esp = %esp – 4, Mem[%esp] = Src
		"		popS Dest							\n" // Dest = Mem[%esp], %esp = %esp + 4
		"		call label							\n" // push address of next instruction, jmp label
		"		ret									\n" // %eip = Mem[%esp], %esp = %esp + 4
		
		// Data Size Suffixes:
		// 		S 	is the size and must be one of:
		//		b 	byte (1 byte)
		//		w 	word (2 bytes) - based on old hardware where word size was 2 bytes
		//		l 	long (4 bytes)
		//		q 	quad words (8 bytes)

		// Condition Flags:
		//		OF 	overflow flag; set when a signed arithmetic operation is either too large or too small to fit in the destination; set when operands have same sign and sign changes
		//		CF 	carry flag; set when an unsigned arithmetic operation is too large to fit in the destination
		//		ZF 	zero flag; set when the result is zero; it is ON if a comparison shows values are equal
		//		SF 	sign flag; set when the result is a negative value
		//		PF 	parity flag; its parity is even (PE) when an even number of 1 bits in the 8 low order bits.
		
		// Integer Registers (4 byte):
		//		%eip 	instruction pointer
		// 		%esp 	stack pointer
		// 		%ebp 	base pointer for stack frame
		// 		%eax 	return values; low of pair for mul/div with %edx; intermediate
		// 		%edx 	high of pair for mul/div pair with %eax; intermediate
		// 		%ecx 	intermediate
		// 		%ebx 	base address for arrays; callee save
		// 		%esi 	source index; callee save
		// 		%edi 	destination index; callee save
		
		// Constants (immediate):
		// 		$constant 	Numeric constants can be base-10 or hexadecimal (begin with 0x).

		// Memory References:
		// 		symbol 				global basis, external or static variable
		// 		$symbol 			address of the variable
		// 		(%reg) 				address in %reg register
		// 		off(%reg)			address = offset + (%reg)
		// 		(%reg1,%reg2) 		address= (%reg1)+(%reg2)
		// 		off(%reg1,%reg2) 	address=offset+(%reg1)+(%reg2)
		// 		off(%reg1,%reg2,sh) address=offset+(%reg1)+(%reg2)*sh where sh is one of 1,2,4,8
		
		// Examples:
		"		mov		$0x89ABCDEF, %%eax			\n"
		"		mov		$0xFF, %%bl					\n"
		"		movsx	%%bl, %%eax					\n"
		"		movzx	%%bl, %%eax					\n"
		
		// two instructions in one asm statement
		// (not a good idea, but interesting that you can do this)
		"		mov	 	$0x12, %%al	\n		mov		$0x34, %%ah\n"

		// swapping two values
		"		mov		$0xBBBBBBBB, %%ebx			\n"
		"		mov		$0xAAAAAAAA, %%eax			\n"
		"		xchg	%%ebx, %%eax				\n"

		// extended asm
		"		mov		%[localVarIn], %%eax		\n" // store localVar into eax
		"		add		$4, %%eax					\n" // set register
		"		mov		%%eax, %[localVarOut]		\n" // add register to localVar

		// int array
		"		mov		$3, %%ecx					\n" // initialize ecx
		"		lea		%[intArray], %%ebx			\n" // load address of start of array
		"		mov		(%%ebx), %%eax				\n" // get first element of array
		"		mov		(%%ebx, %%ecx, 4), %%eax	\n" // get indexed element of array

		// char array
		"		mov		$0, %%eax					\n" // clear eax
		"		lea		%[charArray], %%ebx			\n" // load address of start of array
		"		mov		(%%ebx), %%al				\n" // get first element of array
		"		mov		(%%ebx, %%ecx, 1), %%al		\n" // get indexed element of array

		// conditional statement
		"		cmp		$3, %[localVarIn]			\n" // comparison operation
		"		jg		gt							\n" // conditional jump if > 3
		"		nop									\n" // didn't jump
		"gt:	nop									\n" // conditional jump target

		// floating point load, store
		"		fldl	%[fpVarIn]					\n" // load fpVar onto floating point stack
		"		fld		%%st						\n" // duplicate value on top of fp stack
		"		faddp								\n" // add the two values on the fp stack and pop stack
		"		fstpl	%[fpVarOut]					\n" // store the sum back into fpVar
		
		// floading point operations
		"		f2xm1								\n" // Compute 2^(ST(0))-1 in ST(0)
		"		fabs								\n" // Absolute value of ST
		"		fadd	%[fpVarIn]					\n" // Add fpVarIn (m32/64fp)to ST(0) or ST(i) and store in ST(0)
		"		fadd	%%ST(i), %%ST(0)			\n" // Add ST(i) to ST(0) store in ST(0)
		"		fadd	ST(0), ST(i)				\n" // Add ST(0) to ST(i) store in ST(i)
		"		faddp	ST(0), ST(i)				\n" // Add ST(0) to ST(i) store in ST(i) and pop reg stack		
		"		faddp								\n" // Add ST(0) to ST(1) store in ST(i) and pop reg stack		
		"		fiadd	%[fpVarIn]					\n" // Add fpVarIn (m16/32int) to ST(0)
		"		fbld	%[fpVarIn]					\n" // Convert Binary Coded Decimal (BCD) in fpVarIn (m80dec) to floating point and push to FPU stack
		"		fbstp	%[fpVarOut]					\n" // Store ST(0) as BCD in fpVarOut (m80bcd)
		"		fchs								\n" // Change sign of ST(0)
		"		fclex								\n" // Clear FPU exception flags after checking for pending unmasked fpu exceptions
		"		fnclex								\n" // Clear FPU exception flags without checking for pending unmasked fpu exceptions
		"		fcmovb 	ST(0), ST(i)				\n" // Conditional Move if below (CF=1)	
		"		fcmove 	ST(0), ST(i)				\n" // Conditional Move if equal (ZF=1)	
		"		fcmovbe ST(0), ST(i)				\n" // Conditional Move if below or equal (CF=1 or ZF=1)	
		"		fcmovu 	ST(0), ST(i)				\n" // Conditional Move if unordered (PF=1)	
		"		fcmovnb ST(0), ST(i)				\n" // Conditional Move if not below (CF=0)	
		"		fcmovne ST(0), ST(i)				\n" // Conditional Move if not equal (ZF=0)	
		"		fcmovnbe	ST(0), ST(i)			\n" // Conditional Move if not below or equal (CF=0 and ZF=0)	
		"		fcmovnu ST(0), ST(i)				\n" // Conditional Move if not unordered (PF=0)	
		"		fcom	%[fpVarIn]					\n" // Compare fpVarIn (m32/64fp) with ST(0)
		"		fcom	ST(i)						\n" // Compare ST(i) with ST(0)
		"		fcom								\n" // Compare ST(1) with ST(0)
		"		fcomp	%[fpVarIn]					\n" // Compare fpVarIn (m32/64fp) with ST(0)and pop reg stack
		"		fcomp	ST(i)						\n" // Compare ST(i) with ST(0)and pop reg stack	
		"		fcomp								\n" // Compare ST(1) with ST(0) and pop stack		
		"		fcompp								\n" // Compare ST(1) with ST(0) and pop stack twice	
		"		fcomi	ST, ST(i)					\n" // Compare ST(i) with ST(0) set status flags
		"		fcomip	ST, ST(i)					\n" // Compare ST(i) with ST(0) set status flags and pop reg stack
		"		fucomi	ST, ST(i)					\n" // Compare ST(i) with ST(0) set status flags check for ordered values
		"		fucomip	ST, ST(i)					\n" // Compare ST(i) with ST(0) set status flags check for ordered values and pop reg stack		
		"		fcos								\n" // Cosine of ST(0)
		"		fdecstp								\n" // Decrement Stack-Top Pointer, rotates stack one position ST(0)->ST(7)
		"		fdiv	%[fpVarIn]					\n" // Divide ST(0) by fpVarIn (m32/64fp) store in ST(0)
		"		fdiv	ST(i), ST(0)				\n" // Divide ST(0) by ST(i) store in ST(0)
		"		fdiv	ST(0), ST(i)				\n" // Divide ST(i) by ST(0) store in ST(i)
		"		fdivp	ST(0), ST(i)				\n" // Divide ST(i) by ST(0) store in ST(i) and pop stack
		"		fdivp								\n" // Divide ST(1) by ST(0) store in ST(1) and pop stack		
		"		fidiv	%[fpVarIn]					\n" // Divide ST(0) by fpVarIn (m16/32int) and store in ST(0)
		"		fidivr	%[fpVarIn]					\n" // Divide fpVarIn (m32/64fp) by ST(0) store in ST(0)
		"		fidivr	ST(i), ST(0)				\n" // Divide ST(i) by ST(0) store in ST(0)
		"		fidivr	ST(0), ST(i)				\n" // Divide ST(0) by ST(i) store in ST(i)	
		"		fdivrp	ST(0), ST(i)				\n" // Divide ST(0) by ST(i) store in ST(i) and pop stack
		"		fdivrp								\n" // Divide ST(0) by ST(1) store in ST(1) and pop stack		
		"		fidivr	%[fpVarIn]					\n" // Divide fpVarIn (m16/32int) by ST(0) and store in ST(0)
		"		ffree	ST(i)						\n" // Set tag fo ST(i) to empty
		"		ficom	%[fpVarIn]					\n" // Compare ST(0) with fpVarIn(m16/32int)
		"		ficomp	%[fpVarIn]					\n" // Compare ST(0) with fpVarIn(m16/32int) and pop stack
		"		fild	%[fpVarIn]					\n" // Push fpVarIn(m16/32/64int) onto FPU stack
		"		fincstp								\n" // Increment top field in FPU status reg, rotates stack one position ST(7)->ST(0)
		"		finit								\n" // Initialize FPU after checking for pending unmasked fpu exceptions
		"		fninit								\n" // Initialize FPU without checking for pending unmasked fpu exceptions
		"		fist	%[fpVarOut]					\n" // Store ST(0) in fpVarOut (m16/32int)
		"		fistp	%[fpVarOut]					\n" // Store ST(0) in fpVarOut (m16/32/64int) and pop stack
		"		fisttp	%[fpVarOut]					\n" // Store ST(0) truncated in fpVarOut (m16/32/64int) and pop stack
		"		fld		%[fpVarIn]					\n" // Push fpVarIn (m32/64/80fp) onto FPU stack
		"		fld		ST(i)						\n" // Push ST(i) onto FPU stack
		"		fld1								\n" // Push +1.0 onto FPU stack
		"		fldl2t								\n" // Push log_2(10) onto FPU stack
		"		fldl2e								\n" // Push log_2(e) onto FPU stack
		"		fldpi								\n" // Push pi onto FPU stack
		"		fldlg2	  							\n" // Push log_10(2) onto FPU stack
		"		fldln2								\n" // Push log_e(2) onto FPU stack
		"		fldz								\n" // Push +0.0 onto FPU stack
		"		fldcw	%[fpVarIn]					\n" // Load FPU control word from fpVarIn (m2byte)
		"		fldenv	%[fpVarIn]					\n" // Load FPU enviornment from fpVarIn (m14/28byte)
		"		fmul	%[fpVarIn]					\n" // Multiply ST(0) by fpVarIn (m32/64fp) store in ST(0)
		"		fmul	ST(i), ST(0)				\n" // Multiply ST(i) ST(0) store in ST(0)
		"		fmul	ST(0), ST(i)				\n" // Multiply ST(0) ST(i) store in ST(i)
		"		fmulp	ST(0), ST(i)				\n" // Multiply ST(0) ST(i) store in ST(i) and pop register stack
		"		fmulp								\n" // Multiply ST(0) by ST(1) store in ST(1) and pop register stack
		"		fimul	%[fpVarIn]					\n" // Multiply ST(0) by fpVarIn (m16/32int) and store in ST(0)
		"		fnop								\n" // No operation
		"		fpatan								\n" // Arctan of ST(1)/ST(0) store in ST(1) and pop regiser stack
		"		fprem								\n" // Divide ST(0)/ST(1) store remainder in ST(0)
		"		fprem1								\n" // Divide ST(0)/ST(1) store IEEE remainder in ST(0)
		"		fptan								\n" // Tangent of ST(0) store in ST(0) and push 1 onto FPU stack
		"		frndint								\n" // Round ST(0) to integer
		"		frstor	%[fpVarIn]					\n" // Load FPU state from fpVarIn (m94/108byte)
		"		fsave	%[fpVarOut]					\n" // Store FPU state to fpVarOut (m94/108byte) after checking pending unmasked FPU exceptions
		"		fnsave	%[fpVarOut]					\n" // Store FPU state to fpVarOut (m94/108byte) without checking pending unmasked FPU exceptions
		"		fscale								\n" // Scale ST(0) by ST(i)
		"		fsin								\n" // Sine of ST(0) store in ST(0)
		"		fsincos								\n" // Sine and cosine of ST(0) store sine in ST(0) and push cosine to register stack
		"		fsqrt								\n"	// Sqaure root of ST(0) store in ST(0)
		"		fst		%[fpVarOut]					\n"	// Store ST(0) to fpVarOut (m32/64fp)
		"		fst		ST(i)						\n"	// Store ST(0) to ST(i)
		"		fstp	%[fpVarOut]					\n"	// Store ST(0) to fpVarOut (m32/64/80fp) and pop register stack
		"		fstp	ST(i)						\n"	// Store ST(0) to ST(i) and pop regiter stack
		"		fstcw	%[fpVarOut]					\n"	// Store FPU control word to fpVarOut (m2byte) after checking pending unmasked FPU exceptions
		"		fnstcw	%[fpVarOut]					\n"	// Store FPU control word to fpVarOut (m2byte) without checking pending unmasked FPU exceptions
		"		fstenv	%[fpVarOut]					\n"	// Store FPU environment to fpVarOut (m14/28byte) after checking pending unmasked FPU exceptions
		"		fnstenv	%[fpVarOut]					\n"	// Store FPU enviornment to fpVarOut (m14/28byte) without checking pending unmasked FPU exceptions
		"		fstsw	%[fpVarOut]					\n"	// Store FPU status word to fpVarOut (m2byte) after checking pending unmasked FPU exceptions
		"		fstsw	%%ax						\n"	// Store FPU status word to AX register after checking pending unmasked FPU exceptions
		"		fnstsw	%[fpVarOut]					\n"	// Store FPU status word to fpVarOut (m2byte) without checking pending unmasked FPU exceptions
		"		fnstsw	%%ax						\n"	// Store FPU status word to AX register after without pending unmasked FPU exceptions
		"		fsub	%[fpVarIn]					\n"	// Subtract fpVarIn (m32/64fp) from ST(0) store in ST(0)
		"		fsub	ST(i), ST(0)				\n"	// Subtract ST(i) from ST(0) store in ST(0)
		"		fsub	ST(0), ST(i)				\n"	// Subtract ST(0) from ST(i) store in ST(i)
		"		fsubp	ST(0), ST(i)				\n"	// Subtract ST(0) from ST(i) store in ST(i) and pop register stack
		"		fsubp								\n"	// Subtract ST(0) from ST(1) store in ST(1) and pop register stack
		"		fisub	%[fpVarIn]					\n"	// Subtract fpVarIn (m16/32int) from ST(0) store in ST(0)
		"		fsubr	%[fpVarIn]					\n"	// Subtract ST(0) from fpVarIn (m32/64fp) store in ST(0)
		"		fsubr	ST(i), ST(0)				\n"	// Subtract ST(0) from ST(i) store in ST(0)
		"		fsubr	ST(0), ST(i)				\n"	// Subtract ST(i) from ST(0) store in ST(i)
		"		fsubrp	ST(0), ST(i)				\n"	// Subtract ST(i) from ST(0) store in ST(i) and pop register stack
		"		fsubrp								\n"	// Subtract ST(1) from ST(0) store in ST(1) and pop register stack
		"		fisubr	%[fpVarIn]					\n"	// Subtract ST(0) from fpVarIn (m16/32int) store in ST(0)
		"		ftst								\n"	// Compare ST(0) with +0.0
		"		fucom	ST(i)						\n"	// Compare ST(0) with ST(i)
		"		fucom								\n"	// Compare ST(0) with ST(1)
		"		fucomp	ST(i)						\n"	// Compare ST(0) with ST(i) and pop register stack
		"		fucomp								\n"	// Compare ST(0) with ST(1) and pop register stack
		"		fucompp								\n"	// Compare ST(0) with ST(1) and pop register stack twice		
		"		fxam								\n"	// Classify value or number in ST(0)	
		"		fxch	ST(i)						\n"	// Exchange ST(0) and ST(i)
		"		fxch								\n"	// Exchange ST(0) and ST(1)
		"		fxrstor	%[fpVarIn]					\n"	// Restore x87 FPU, MMX, XMM, and MXCSR from fpVarIn (m512byte)
		"		fxsave	%[fpVarOut]					\n"	// Save x87 FPU, MMX, XMM, and MXCSR to fpVarOut (m512byte)
		"		fxtract								\n"	// Extract exponenet and significand from ST(0) store exponenet in ST(0) and push sig onto reg stack
		"		fyl2x								\n"	// Compute ST(1)*log_2(ST(0)) store in ST(1) and pop reg stack
		"		fyl2xp1								\n"	// Compute ST(1)*log_2(ST(0)+1.0) store in ST(1) and pop reg stack
		
		: [localVarOut]		"=m"	(localVar),		// output %0
		  [fpVarOut]		"=m"	(fpVar)			// output %1
		: [localVarIn]		"m"		(localVar),		// input %2
		  [intArray]		"m"		(intArray),		// input %3
		  [charArray]		"m"		(charArray),	// input %4
		  [fpVarIn]			"m"		(fpVar)			// input %5
		: "eax", "ebx", "ecx"						// clobbers
	);

	return 0;
}
