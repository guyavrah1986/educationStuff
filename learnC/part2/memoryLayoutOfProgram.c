//==========================================================================================================================================================
//==========================================================================================================================================================
// Memory layout and compilation-linking-loading relationship:
// ===========================================================
// 1.The text segment is the section of the program that contains, mainly, the final machine code that is to be loaded and executed on the target machine.
//   - It also contains, for example, string literals.
//   - It is a read-only memory region.
//   - Every local variable that is defined in one of the functions of the program, in either source (.c) file, also contributes to the final size of the
//   the text segment.
//   
// NOTE: In order to eliminate the code that is added to the final executable by the run-time C library, compile the program as follows:
//       $ gcc -nostdlib memoryLayoutOfProgram.c -o memoryLayoutOfProgram
// The following error/notation might rise: /usr/bin/ld: warning: cannot find entry symbol _start; defaulting to 00000000000002b1
//
// 1.1 Only main program
//   size memoryLayoutOfProgram
//   text	   data	    bss	    dec	    hex	filename
//   211	    224	      0	    435	    1b3	memoryLayoutOfProgram
//
// 1.2 Main program with one local variable that is NOT initialized:
//   size memoryLayoutOfProgram
//   text	   data	    bss	    dec	    hex	filename
//   211	    224	      0	    435	    1b3	memoryLayoutOfProgram
//
// 1.3 Main program with one local variable that is initialized:
//   size memoryLayoutOfProgram
//   text	   data	    bss	    dec	    hex	filename
//   218	    224	      0	    442	    1ba	memoryLayoutOfProgram
//
// IMPORTANT NOTE: The additional 7 bytes that were added to the text size is NOT due to the int that was added.
//
// 1.4 Main program and func1 WITHOUT local variable 
//   size memoryLayoutOfProgram
//   text	   data	    bss	    dec	    hex	filename
//   265	    224	      0	    489	    1e9	memoryLayoutOfProgram
//
// 1.5 Main program and func1 with local variable 
//   size memoryLayoutOfProgram
//   text	   data	    bss	    dec	    hex	filename
//   286	    224	      0	    510	    1fe	memoryLayoutOfProgram
//
// IMPORTANT NOTE: Just as in 1.3, the additional bytes that were added to the text segment are NOT because of the local 
//                 variable of func1 (of type double).
//
// 1.6 Main program with both func1 and func2 and their local variables.
//   size memoryLayoutOfProgram
//   text	   data	    bss	    dec	    hex	filename
//   340	    224	      0	    564	    234	memoryLayoutOfProgram
// 
// 1.7 Main program + 2 funcs + global variable NOT initialized
//   size memoryLayoutOfProgram
//   text	   data	    bss	    dec	    hex	filename
//   340	    224	      8	    572	    23c	memoryLayoutOfProgram
//
// IMPORTANT NOTE: Pay attention that the bss is "finally" NOT zero but 8 bytes.
//
// 1.8 Same as 1.7 and global variable that is initialized
//  size memoryLayoutOfProgram
//  text	   data	    bss	    dec	    hex	filename
//  340	    	   228	      4	    572	    23c	memoryLayoutOfProgram
//
// IMPORTANT NOTES: The size of the data increased by 4 - which is the size of the globalIntVarInitialized --> which is fine!
//                  But also, the size of the bss decreased from 8 --> 4, this is becasue the sum of: bss + data MUST be divided by 8
// 
// 1.9 Same as 1.8 and global static variable that is NOT initialized
//   size memoryLayoutOfProgram
//   text	   data	    bss	    dec	    hex	filename
//   340	    228	     12	    580	    244	memoryLayoutOfProgram
//
// 1.10 Same as 1.9 and global static variable that is initialized
//   size memoryLayoutOfProgram
//   text	   data	    bss	    dec	    hex	filename
//   340	    230	      8	    578	    242	memoryLayoutOfProgram
//
// 1.11 Same as 1.9 and global const char* string initialized
//   size memoryLayoutOfProgram
//   text	   data	    bss	    dec	    hex	filename
//   372	    288	      8	    668	    29c	memoryLayoutOfProgram
//
//
// IMPORTANT NOTES: The size of the data increased by 2 - which is the size of the globalStaticInitialized (short) --> which is fine!
//                  But also, the size of the bss decreased from 12 --> 8, this is becasue (again) the sum of: bss + data MUST be divided by 8
//
// 2. Summary/points to think of:
//    - The size of the executable on the disk is defined by the text + data segment, i.e. - the bss segment is only created when the program is
//      loaded into main memory and all of it is "easily" set to 0 by memset.
//    - The stack of a program, is only relevant once it is running. It allocates and de-allocates "itself" without any intervention from the 
//      programmer.
//
// Good links:
// -----------
// https://stackoverflow.com/questions/46376679/why-data-segment-of-c-was-separated-as-two-sections?noredirect=1&lq=1
//
//==========================================================================================================================================================
//==========================================================================================================================================================

#include <stdio.h>

int globalIntVarNotInitialized;
int globalIntVarInitialized = 17;
static short globalStaticNotInitialized;
static short globalStaticInitialized = 15;
const char* str1 = "string1";

void func1()
{
	double localVarFunc1 = 8.5;
}


void func2()
{
	int localVarFunc2 = 3;
}


int main(int argc, char** argv)
{
	int localVarMainFunc = 4;
}
