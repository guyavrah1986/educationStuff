// ==============================================================================================
// ==============================================================================================
//
//
// ==============================================================================================
// ==============================================================================================
#include <stdio.h>

struct myConstStruct
{
  int a;
  int b;
};

/* 4)
const struct myConstStruct2
{
  int a;
  int b;
}; //--> struct myConstStruct
*/

void ConstQualifierExample()
{
    const char funcName [] = "ConstQualifierExample - ";
    printf("%s start\n", funcName);
    
    // 1)
    // Declration: Normal and minimal declration of some type specifier, in this case int
    // Storage location: It is defined on the function's stack.
    // Duration: Lives thrghout the lifetime of this function.
    // Modification: It can be modified at any given time.
    int x = 12;
    printf("%s defined an int named x with value of:%d\n", funcName, x);

    // 2) 
    // Declration: Normal int + one qualifier - const
    // Storage location: It is implementation dependent. In gcc, const varibles
    // are typically located in the text segmment (which is read-only section).
    // Duration: Depending on the location in which it was sotred.
    // Notes: A const variable in C can be un-initialized when it is declared.
    const int y = 17;
    
    // 2.1) Accessing in a "mal form" way to the const variable, can cause an
    // undefined behaviour
    int* pointerY = (int *)&y;
    printf("%s pointerY's address is:%p, and the value it is pointing to is:%d\n", funcName, pointerY, *pointerY);
    
    // change the const int value via a pointer to it
    *pointerY = 15;
    printf("%s pointerY's address is:%p, and the value it is pointing to is:%d\n", funcName, pointerY, *pointerY);

    // y = 12;
    const int z;
    
    // 3) 
    // When adding the const qualifier to pointer variable, it is CRUCIAL to 
    // point WHERE was it added: BEFORE or AFTER the *:
    // p1 is a pointer to a constant C-style string literal
    // p2 is a consttant pointer to a C-style string literal
    
    // 3.1) 
    const char* p1 = "abcd";
    printf("%s initially, p1 points to the C-style stirng:%s, at address:%p\n", funcName, p1, p1);
    // p1[2] = 'e'; --> error: assignment of read-only location ‘*(p1 + 2)’
    p1 = "hijk";
    printf("%s after re-setting it, p1 points to the C-style stirng:%s, at address:%p\n", funcName, p1, p1);

    // 3.2)
    char* p3 = "rotem";
    printf("%s defined another C-style string literal pointed by p3 at address:%p, with content:%s\n", funcName, p3, p3);
    char* const p2 = "efgh";
    printf("%s defined another const C-style string literal pointed by p2 at address:%p, with content:%s\n", funcName, p2, p2);
    //p2 = p3; --> error: assignment of read-only variable ‘p2’
    
    
    // 4) See also above: 
    const struct myConstStruct s1 = {12, 15};
    printf("%s defined struct myConstStruct s1 as a CONST instant of this struct type. Its a1 value is:%d\n", funcName, s1.a);
    printf("%s end\n", funcName);
}

int main()
{
    printf("main - start\n");
    
    ConstQualifierExample();
    
    printf("main - end\n");
    return 0;
}
