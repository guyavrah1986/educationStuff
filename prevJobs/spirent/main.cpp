//======================================================================================================================
// This example shows how to call C function from within C++ code that passes class into its respective struct in C 
// 1. Non working example:
// 1.1 g++ -Wall -c -o main.o -std=c++98 main.cpp  --> creates main.o
// 1.2 gcc -c -o c.o -std=c90 c.c                  --> ctreats c.o
// 1.3 g++ -o main.out main.o c.o	  	   --> creates main.out
// If you do NOT add the extern C in the c.h file where the funcThatGetPointerToCppClassAndTreatItAsStrcut is used, 
// because g++ expctes to see "mangled" name for the funcThatGetPointerToCppClassAndTreatItAsStrcut but it does NOT find
// such one (cause gcc does NOT mangle names).
//
// 2. Class virtual pointer passed to C code:
// 2.1 When a class has at least one virtual function,the compiler adds to it the virtual pointer. Typically, it will
//     reside as the first member of the class, i.e. - "member 0" - therefor, if it is being "C styled" parsed, the 
//     offsets used need to be adjust.
// 
// https://stackoverflow.com/questions/1041866/what-is-the-effect-of-extern-c-in-c
//======================================================================================================================
#include <iostream>
#include <string>

#include "c.h"

using namespace std;

class SampleClass
{
public:
	SampleClass(int x, int y, char c) : m_x(x), m_y(y), m_c(c)
	{
		cout << "SampleClass::SampleClass - set m_x:" << m_x << ", m_y:" << m_y << ", m_c:" << m_c << endl;
	}
	
	virtual ~SampleClass()
	{
		cout << "SampleClass::~SampleClass" << endl;
	}

	int m_x;
	int m_y;
	char m_c;
};

using namespace std;

int main(int argc, char** argv)
{
	string funcName = "main - ";
	cout << funcName + "start" << endl;
	struct sampleStruct pStruct;
	pStruct.x = 12;
	pStruct.y = 15;
	pStruct.c = 'a';
	SampleClass sampleClass(12, 15, 'a');
	cout << funcName + "sizeof SampleClass is:" << sizeof(SampleClass) << endl;
	cout << funcName + "sizeof sampleStruct is:" << sizeof(sampleStruct) << endl;
	cout << funcName + "passing pointer to a SampleClass object in address:" << static_cast<void*>(&sampleClass) << endl;
	funcThatGetPointerToCppClassAndTreatItAsStrcut(&sampleClass);
	cout << funcName + "end" << endl;	
	return 0;
}

