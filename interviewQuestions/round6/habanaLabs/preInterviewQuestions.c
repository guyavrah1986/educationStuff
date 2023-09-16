#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>


/*
Currently the assumption is that every word is separated from the next one by exactly
one ' ' (space character). If later another assumption is made, change the 
implementation of this function.
*/
char* forwardStringPointerToNextWord(char* origStr)
{
    while (' ' == *origStr)
    {
        ++origStr;
    }
    
    return origStr;
}

/*
This function gets a pointer to a string that might contain several words (i.e.
 - sub strings within it that are separate by space character). Its role is to
extract the "current word", i.e. - iterating over the "big" string till it hits
either space (' ') or the NULL terminator that basically indicates that this is 
the last word in the string.
The function returns the length of the current word.
*/
size_t extractWordFromString(char* str)
{
    const char funcName [] = "extractWordFromString - ";
    printf("%s got the string:%s\n", funcName, str);
    size_t currWordLen = 0;
    while (*str != ' ' && *str != '\0')
    {
        ++str;
        ++currWordLen;
    }
    
    return currWordLen;
}

void reverseWord(char* str, size_t strLen)
{
    const char funcName [] = "reverseWord - ";
    //size_t strLen = strlen(src);
    printf("%s got the word(string):%s, at address:%p, with size:%lu\n", funcName, str, (void*)str, strLen);
    for (uint8_t startIndex = 0, endIndex = strLen - 1; startIndex < endIndex; ++startIndex, --endIndex)
    {
        char tmp = str[startIndex];
        printf("%s startIndex:%u, endIndex:%u, tmp is:%c\n", funcName, startIndex, endIndex, tmp);
        str[startIndex] = str[endIndex];
        str[endIndex] = tmp;
    }
    
    printf("%s finally the string is now:%s\n", funcName, str);
}

void reverseStringWithSeveralWords(char* origStr)
{
    const char funcName [] = "reverseStringWithSeveralWords - ";
    size_t strLen = 0;
    char* tmp = origStr;
    while ((*tmp) != '\0')
    {
        ++strLen;
        ++tmp;
    }
    
    printf("%s the original string is:%s with length of:%lu characters\n", funcName, origStr, strLen);
    
    // iterate over the string, and parse each word by hitting the space char
    // or the '\0' that indicates that it is the last word in the string
    char* reversedStringWithWords = (char*)malloc((sizeof(char) * strLen) + 1);
    printf("%s allocated %lu bytes for the reversed string\n", funcName, strLen + 1);
    
    // first reverse the entire string as a whole
    reverseWord(origStr, strLen);
    printf("%s after reversing the entire string as a whole it is:%s\n", funcName, origStr);
    
    
    while (*origStr != '\0')
    {
        size_t currWordLen = extractWordFromString(origStr);
        reverseWord(origStr, currWordLen);
        origStr += currWordLen;
        
        // move on to the next word or to the end of the main string (the 
        // terminating NULL character)
        origStr = forwardStringPointerToNextWord(origStr);    
    }
}

int main()
{
    printf("main - start\n");
    
    /*
    char str [] = "abcd";
    size_t len = strlen(str);
    printf("main - str at the begining is:%s, with length of:%lu, located at address:%p\n", str, len, str);
    reverseWord(str, len);
    printf("main - after reversing the string is:%s\n", str);
    */
    
    char strWithSeveralWords [] = "ab cd";
    reverseStringWithSeveralWords(strWithSeveralWords);
    printf("main - after reversing the entire word, it is now:%s\n", strWithSeveralWords);
    return 0;
}
