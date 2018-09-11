/*
* First interview question:
* -------------------------
* Implement a simple regex match finder.
* 1) Given alpha-bet for str is [a-z] only.
* 2) (*) - means 0 chars or more.
* 3) (?) - means 1 chars or more.
* 4) If a given pattern ends with a character --> than str MUST end with it as well.
* 5) A pattern can end with a "wild card" (? or *).
* 6) You can assume pattern and str contains only [a-z] and [? *]  
*
* NOTES:
* a) Initial code is the code provided below.
* b) For the first implementation there is no need for efficiency -- just get it work.
*/


#include <iostream>

using namespace std;

bool isMatch(const char* str, const char* pattern)
{
	return false;
}


bool RunFirstInterviewQuestion()
{
	cout << "RunFirstInterviewQuestion - start" << endl;
	cout << "isMatch(abcd, ab?d) returns:" << (isMatch("abcd", "ab?d") == true) << endl;	// Should return true
	cout << "isMatch(ab, a*b) returns:" << (isMatch("ab", "a*b") == true) << endl;		// should return true
	cout << "isMatch(ab, a*b) returns:" << (isMatch("ab", "a?b") == true) << endl;		// should return false
	cout << "RunFirstInterviewQuestion - end" << endl;
}
