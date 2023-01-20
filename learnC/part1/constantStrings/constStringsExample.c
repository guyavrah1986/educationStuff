// =================================================================================================================================
// =================================================================================================================================
// Part 1 - constant strings:
// --------------------------
// This example illustrate the correct usage of "C-style" strings in a program.
// 1) When a C-style string is defined in this manner (const char* str = ...) it automatically being allocated (by the compiler)
//    within the TEXT segment of the program - which is by definition a READ-ONLY memory part. Therefor, any attempt to modify
//    the contents of a C-style string defined like so - will (propably) cause a segmentation fault error. Also, note that, if 
//    two (or more) different char* as such are set to "point" to the EXACT same string - than all of them will point to the 
//    same address location in the TEXT segment where this string is placed.
// 2) Due to the fact that was mentioned before, we CAN NOT assgin "new" value to a "TEXT segment" C-style string - so the 
//    attempt in the comment in this case will also cause the progrma to crash. NOTE: Even if the const is removed from the 
//    string literal variable - it is still NOT allowed to modify it. 
// 3) This is a correct way to copy one (const) string into another.
// 
//
// =================================================================================================================================
// =================================================================================================================================
#include <stdio.h>
#include <string.h>

void sameStringInDifferentPointers()
{
	const char* str2 = "str2";	
	const char* str3 = "str2";
	printf("sameStringInDifferentPointers - address of str2 is:%p, address of str3 is:%p \n", str2, str3);	//1)
}

void copyStringIntoStringLiteral()
{
	printf("copyStringIntoStringLiteral - start\n");
	char* stringLiteral = "abcde";
	const char stringToCopy [] = "abcd";	// 2)
	/*	
	strcpy(stringLiteral, "abcd");
	printf("copyStringIntoStringLiteral - after copying stringToCopy which is:%s to stringLiteral, stringLiteral is:%s \n", stringToCopy, stringLiteral);
	*/
}

void correctWayToCopyString()
{
	char str1[] = "str1";
	char dstStr[5];	
	
	strcpy(dstStr, str1);	//3)
	printf("correctWayToCopyString - after copying str1 which is:%s to dstStr, dstStr is:%s \n", str1, dstStr);
}

// ================================
// ================================

int main()
{
	printf("main - start \n");
	
	sameStringInDifferentPointers();
	copyStringIntoStringLiteral();
	correctWayToCopyString();

	printf("main - end \n");
	return 0;
}
