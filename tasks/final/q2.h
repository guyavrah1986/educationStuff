/*
* Write implement the method so that each number will be printed in the given base:
* a) print_num(123,10) --> 123
* b) print_num(17,2) --> 10001
* c) print_num(20,16) --> 14
*
*/

#include <iostream>

using namespace std;

void print_num(unsigned int num, unsigned int base)
{
	cout << "print_num - got num:" << num << " and base:" << base << endl;
	const size_t numOfCharacters = 16;
	const static unsigned char arr [] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
}

