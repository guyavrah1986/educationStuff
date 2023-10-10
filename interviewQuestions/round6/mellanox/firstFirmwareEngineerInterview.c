// 1. Implement a function to check whether a system (target) is big OR littel endian
// bool IsBigEndian();

// 2. Does an application is/should be aware of whether she runs on a big Vs. littele endian

// 3. a = 1
//    b = a << 3;
//    Does it matter if the target machine is big or littel 
//     ANSWER: Aside from networking "interoperability" between different archtiectures that requieres, for example, usage in the nthos() method, the application is UNAWARE 
//     of it.

// 4. Why there is a compilation error in the code below:
void question4()
{
  void* v_ptr;
  int a = 5;
  v_ptr = &a;
  *v_ptr = 6;
}

// 5. void question5()
{  
  

}

// 6. Are you familiar with any qualifiers in the C language
// ANSWER: auto, static, 

// 7. What is the difference between typedef and DEFINE

// 8. Why does printf show 16?
void question8()
{
    typedef struct dum 
    {
      double Time;
      unsigned char a;
    }a_t;

    int i;
     a_t d;
     i = sizeof(d);
     printf("%d\n", i);
}


// 9. Given a string and a char, duplicate all the occurences of the special string if/wehn applicable.
// For example: 
// string = sedfrt  and ch = d --> seddfr
void duplicateCharAppearences(const char charToDuplicate, char* str)
{
    const char funcName [] = "duplicateCharAppearences - ";
    if (NULL == str)
    {
        printf("%s got a NULL string, terminating\n", funcName);
        return;
    }
    
    printf("%s got the string:%s and the char:%c\n", funcName, str, charToDuplicate);
    
    // create a new array of characters with the same size of the original string
    size_t strLen = 0;
    char* tmp = str;
    while (*tmp != '\0')
    {
        ++strLen;
        ++tmp;
    }
    
    printf("%s the length of the original string is:%lu\n", funcName, strLen);
    
    // first iteration, go over the original string and "mark every place that has duplicate char"
    char* retStr = (char*)malloc(sizeof(char) * (strLen + 1));
    char indicationChar = '_';
    
    // we iterate untill the character which is one BEFORE the last one, cause if the very last
    // character is the one to duplicate, there is no point of that...
    for (unsigned char i = 0; i < strLen - 1; ++i)
    {
        if (str[i] == charToDuplicate)
        {
            retStr[i + 1] = indicationChar;
        }
    }
    
    printf("%s after only filling the duplicated chars, the temporary string to return is:\n", funcName);
    for (unsigned char i = 0; i < strLen; ++i)
    {
        printf("retStr[%u]:%c\n", i, retStr[i]);
    }
    
    // now fill the rest of the characters which are NOT the charToDuplicate
    for (unsigned char i = 0; i < strLen; ++i)
    {
        if (retStr[i] == indicationChar)
        {
            retStr[i] = charToDuplicate;
        }
        else
        {
            retStr[i] = str[i];
        }
    }
    
    printf("%s after filling also the NON duplicated chars of the original string, the return string is:\n", funcName);
    for (unsigned char i = 0; i < strLen; ++i)
    {
        printf("retStr[%u]:%c\n", i, retStr[i]);
    }
    
    
int main(int argc, char** argv)
{
  const char funcName = "main - ";
  printf("%s start\n");
  printf("%s end\n");
}


/* MY interview final notes for question 9:

sdafl d
sddaf

use cases:
sddkli --> sddddk

seddu --> seddd

qwertd --> qwertd

						
void shiftBytesOnePlace(uint8_t *buff, uint8_t startIndex)
{
	buff[startIndex] = ch;
	memmove((void *)buff + 1, const void *str2, size_t n)
}

void LetsDuplicate(uint8_t *buff, uint8_t ch) {
	size_t strLen = strlen(buff);
	for (size_t i = 0; i < strLen; ++i)
    {
    	if (buff[i] != ch)
        {
        	continue;
        }
        
        // if applicable, do the duplication:
        if (i == strLen - 1)
        {
        	return;
        }
      
      	// save curr value of the current bytes
        uint8_t tmp = buff[++i];
        
        // sdafl --> sdafl 
        // tmp = a , i = 2
      	buff[i] = ch;
        // sddfl
        
        // how many bytes are there till the end of the string
        //size_t bytesLeft = strLen - i;
        for (size_t j = i + 1; j < strLen - 1; ++j, ++i)
        {
        	buff[i] = tmp;
            tmp = buff[i];
        }
        
    }
}
*/
