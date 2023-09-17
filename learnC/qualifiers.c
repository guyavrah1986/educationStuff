// ==============================================================================================
// ==============================================================================================
//
//
// ==============================================================================================
// ==============================================================================================
#include <stdio.h>

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
    
    // 2) 
    // Declration: Normal int + one qualifier - const
    // Storage location: It is implementation dependent. In gcc, const varibles
    // are typically located in the text segmment (which is read-only section).
    // Duration: Depending on the location in which it was sotred.
    // Notes: A const variable in C can be un-initialized when it is declared.
    const int y = 17;
    // y = 12;
    const int z;
    
    // 3) 
    // When adding the const qualifier to pointer variable, it is CRUCIAL to 
    // point WHERE was it added: BEFORE or AFTER the *:
    // p1 is a pointer to a constant C-style string literal
    // p2 is a consttant pointer to a C-style string literal
    const char* p1 = "abcd";
    printf("%s initially, p1 points to the C-style stirng:%s, at address:%p\n", funcName, p1, p1);
    // p1[2] = 'e'; --> error: assignment of read-only location ‘*(p1 + 2)’
    p1 = "hijk";
    printf("%s after re-setting it, p1 points to the C-style stirng:%s, at address:%p\n", funcName, p1, p1);

    char* const p2 = "efgh";
    
    printf("%s end\n", funcName);
}

int main()
{
    printf("main - start\n");
    ConstQualifierExample();
    printf("main - end\n");
    return 0;
}

