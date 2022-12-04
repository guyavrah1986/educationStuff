// ########################################################################################################
// ########################################################################################################
// Logistics: 
// ---------
// To compile this file into an executable (.exe on Windows):
// a) Navigate to the file's folder from the Developer Command Prompt for VS2017.
// b) Type the command: cl /EHsc fileName.cpp
// c) Run the fileName.exe for debugging.
//
// 1) Given a string and a pattern that contains only * wildcards - write a function that returns true
//    if the the given pattern is contained within the string, the original question did not mind the 
//    the language, YET offcourse time & space comlexity is important. 
//
// 2) Given a "very simple machine" with Windows 7 OS 32 bit, single core, you are requested to do the
//    following: 
//    a) A user of a certain computer uses ONLY windows media player in order to listen to music.
//    b) He works from 09:00-18:00 Sunday-Thursday.
//    How would you measure the total amount of time it spends listening to MUSIC via the windows
//    media player ?
//    NOTES:
//    - It might be the case that the Windows media player is "up" (running) YET not playing music, i.e.-
//    performs some update or something like this. 
// 
// ########################################################################################################
// ########################################################################################################
#include <iostream>
#include <stdio.h>

using namespace std;

/*
* This function searches for the first character in subStr that is equal to
* charAfterAstrik. 
* In case it finds one - it returns a pointer to that chracter within the subStr.
* In case it dones not find - it returns NULL.
*/
char* handleAstrik(const char* subStr, char charAfterAstrik)
{
	while ()
}

bool question1(const char* str, const char* pattern)
{
	if(str == NULL || pattern == NULL)
	{
		return false;
	}
	
	cout << "questio1 - got str:" << str << " and pattern:" << pattern << endl;	
	while(*str != '\0' && *pattern != '\0')
	{
		cout << "question1 - *str:" << *str << ", *pattern:" << *pattern << endl;
		if(*str == *pattern)
		{
			str++;
			pattern++;
			continue;
		}
		
		if(*pattern != '*')
		{
			return false;
		}
		
		while(*pattern == '*')
		{
			pattern++;
		}
		
		cout << "question1 - after forwarding pattern, *str:" << *str << ", *pattern:" << *pattern << endl;

		str++;
		pattern++;
	}
	
	// if we got here we had a match
	return true;
}

// ===============================
// main
// ===============================

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	
	
	cout << "main - end" << endl;
	return 0;
}
