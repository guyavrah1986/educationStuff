#include <iostream>

#include "../vptrInClassVsStructInC/sampleClass.h"
#include "../vptrInClassVsStructInC/derivedFromSample.h"

using namespace std;


void structVsClassWithVptrExample()
{
	cout << "structVsClassWithVptrExample - start" << endl;
	struct SampleStruct* sampleStruct = 0;
	char str [] = "abcde";
	DerivedFromSample* sampleClass = new DerivedFromSample(3.14, 17, str);
	sampleStruct = (struct SampleStruct*)sampleClass;
	cout << "sampleStruct->id:" << sampleStruct->id << " and sampleStruct->str:" << sampleStruct->str << endl;
	cout << "structVsClassWithVptrExample - end" << endl;
	delete sampleClass;
}

int main(int argc, char** argv)
{
	cout << "main - Start" << endl;

	structVsClassWithVptrExample();

	cout << "main - End" << endl;
	return 0;
}

