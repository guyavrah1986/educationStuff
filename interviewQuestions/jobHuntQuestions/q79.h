// ====================================================================================================================================
/*
*  question 79:
*  -----------
*  Given a phrase ("string") with 3 different types of paranthesses {([ and their respective ])} - write a method that checks if the 
*  provided phrase is valid or not (each opening parantheses has its corresponding closing paranthesses).
*
*/
// ====================================================================================================================================

#define maxNumOfChars 100

int q79(const char* str)
{
	if (str == NULL)
	{
		printf("q79 - got a NULL string, aborting...\n");
		return 1;
	}

	char stack [maxNumOfChars] = {'\0'};
	size_t sp = 0;
	while (str != '\0')
	{
		if (*str == '{' || *str == '[' || *str == '(')
		{	
			stack[sp] = *str;
			++sp;
		}
		else if (*str == '}' || *str == ']' || *str == ')')
		{
			if (sp <= 0)
			{
				return 1;
			}
			sp--;
			if (*str == '}' && stack[sp] != '{')
			{
				return 1;
			}
			if (*str == ']' && stack[sp] != '[')
			{
				return 1;
			}
		}
		else if (*str == ']')
		{

		}
		else if(*str == '(')
		{

		}
	}
}
