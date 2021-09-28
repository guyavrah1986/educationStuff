#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

void reverseString(char* str, size_t strLen)
{
	string funcName = "reverseString - ";
	cout << funcName + "got original string:" << str << endl;
	size_t numIterations = (strLen / 2);
	cout << funcName + "about to iterate for:" << numIterations << " in order to reverse it" << endl;
	for (size_t i = 0; i < numIterations; ++i)
	{
		char tmp = str[i];
		str[i] = str[strLen -1 - i];
		str[strLen -1 - i] = tmp;
	}
}


char* reverseWordsInsString(char* s)
{
    size_t start = 0;
    size_t len = strlen(s);
    size_t end = len - 1;
    printf("there are:%lu chars in the string\n", end + 1);
    // reverse the entire string
    size_t index = 0;
    size_t numIterations = len / 2;
    printf("about to reverse the string using %lu iterations\n", numIterations);
    size_t i = 0;
    while (i < numIterations)
    {
        char tmp = s[start];
        s[start] = s[end];
        s[end] = tmp;
        
        ++i;
        printf("after iteration %lu, the string is:%s\n", i, s);
        ++start; 
        --end;
    }
    
    printf("after reversing the entire string it is:%s\n", s);
    
    
    // eliminated trailing whitespaces
    i = 0;
    end = len;
    while (s[end - 1] == ' ')
    {
        ++i;
        --end;
    }
    
    // setting the new "end" of string
    s[len - i] = '\0';
    size_t newLen = len - i;
    printf("after eliminating TRAILING whitespaces, the string is:%s with length of:%lu\n", s, newLen);
    
    
    // skip all leading whitespaces
    i = 0;
    while (s[i] == ' ')
    {
        printf("string at[%lu] is whitespace\n", i);
        ++i;
    }
    
    // eliminated all leading whitespace
    start = i;
    s = &s[i];
    printf("after eliminating all LEADING whitespace the string is:%s with length of %lu bytes\n", s, newLen);
    i = 0;
    while (i < newLen)
    {
        if (s[i] == ' ')
        {
            printf("s[%lu] is whitespace, skipping it\n", i);
            ++i;
            continue;
        }
        
        size_t startWord = i;
        size_t currWordIndex = i;
        size_t currWordLen = 0;
        while (s[currWordIndex] != '\0' && s[currWordIndex] != ' ')
        {
            ++currWordLen;
            ++currWordIndex;
        }
        
        // reverse the current word
        --currWordIndex;
        size_t numFlipIterations = currWordLen / 2;
        size_t flipIter = 0;
        while (flipIter < numFlipIterations)
        {
            char tmp = s[currWordIndex];
            s[currWordIndex] = s[startWord];
            s[startWord] = tmp;
            --currWordLen;
            ++startWord;
            --currWordIndex;
            ++flipIter;
        }
        
        i = startWord + 1;
        printf("after reversing a word, the string is:%s\n setting the main index iterator i to:%lu\n", s, i);
    }

    return s;
}

int main(int argc, char** argv)
{
	string funcName = "main - ";
	cout << funcName + "start" << endl;
	char str [] = "abcde";
	char reversedStr [] = "edcba";
	size_t strLen = sizeof(reversedStr) / sizeof(char) - 1;
	cout << funcName + "length of reversedStr is:" << strLen << " bytes" << endl;
	reverseString(str, strLen);
	cout << funcName + "after reversing it, str is:" << str << endl;
	for (size_t i = 0; i < strLen; ++i)
	{
		if (str[i] != reversedStr[i])
		{
			cout << funcName + "str[" << i << "] after reversing it, is invalid" << endl;
			return 1;
		}
	}

	char str2 [] = "the sky is blue";
	cout << "before reversing all words in a string, the string str2 is:" << str2 << endl;
	cout << "after reversing all words in a string, the string str2 is:" << reverseWordsInsString(str2) << endl;

	cout << funcName + "reversed string correctly, it is now:" << str << endl;
	return 0;
}

