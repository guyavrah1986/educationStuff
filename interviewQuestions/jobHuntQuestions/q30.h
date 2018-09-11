// ====================================================================================================================================
/*
*  question 30:
*  -----------
*  Write a method that gets two strings (C style) and comapres between them. The return value is defined as in the strcmp of the 
*  standard library. 
*
*/
// ====================================================================================================================================


int strCmp(const char* str1, const char* str2)
{
	while (*str1 != '\0' && *str2 != '\0')
	{
		int diff = *str1 - *str2;
		if (diff != 0)	
		{
			return diff;
		}

		++str1;
		++str2;
	}

	return *str1 - *str2;
}
