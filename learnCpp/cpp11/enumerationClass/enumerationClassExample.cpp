// =======================================================================================================================
// =======================================================================================================================
// C++11 enumeration class:
// ------------------------
// 1. In the case of old enum, when an enum is declared in global namespace (i.e. - not within any specific namespace), it
//    can "clash" with any other type declared in this namespace.
//    When the program compiled with the commented line, this will be the compiler output:
//    error: ‘const string thirdVal’ redeclared as different kind of symbol
// 2. With the new enum class type in C++11, it is possible to have a value of an enumeration and some variable in the 
//    same namespace --> and they won't "clash".
//
// =======================================================================================================================
// =======================================================================================================================

#include <iostream>

using namespace std;

enum oldTypeEnum
{
	firstVal = 0,
	secondVal,
	thirdVal
};

// 1.
//const string thirdVal = "thirdValString";

// 2.
enum class cpp11EnumClass
{
	val1 = 0,
	val2,
	val3
};

const string val1 = "valString";

int main(int argc, char** argv)
{
	cout << "main - start" << endl;

	//cout << "main - the string variable thirdVal has the value of:" << thirdVal << endl;
	cout << "main - val1 string variable holds the value:" << val1 << endl;
	cout << "main - end" << endl;
	return 0;
}

