#include "sortedArrayAndNumber.h"
#include "basicClassInheritence.h"

void virtualAnNonVirtualFunc()
{
	const char str [] = "rotem"; 
	Derived d(str);
	Base* pb = &d;
	Derived* pd = &d;
	
	// 1) When callign a non virtual function that is implemented BOTH in the Base and Derived
	//    classes from a Derived object - it depends "how" we call it: 
	//  a) Directly with the object --> the Derived's function version will be invoked.
	//  b) Via a Base* --> the Base's function version will be invoked.
	//  c) Via a Derived* --> the Derived's function version will be invoked.
	cout << "main - calling NotVirtualFunc from a Derived object pointed by a Base pointer" << endl;
	pb->NotVirtualFunc();

	cout << "main - calling NotVirtualFunc from a Derived object pointed by a Derived pointer" << endl;
	pd->NotVirtualFunc();


	// 2) When calling a virtual function that is implemented BOTH in the Base and Derived
	//    classes --> no matter how we call the function --> the most derived version will 
	//    be invoked.
	cout << "main - calling VirtualFunc from a Derived object pointed by a Base pointer" << endl;
	pb->VirtualFunc();

	cout << "main - calling VirtualFunc from a Derived object pointed by a Derived pointer" << endl;
	pd->VirtualFunc();

	// 3) Calling a pure virtual function NOT from within the Base class, is just like calling any
	//    other "normal" virtual function --> the Derived's function version will be invoked ALWAYS.
	cout << "main - calling PureVirtualFunc from a Derived object pointed by a Base pointer" << endl;
	pb->PureVirtualFunc();

	cout << "main - calling PureVirtualFunc from a Derived object pointed by a Derived pointer" << endl;
	pd->PureVirtualFunc();

	cout << "main - calling PureVirtualFunc DIRECTLY from a Derived object" << endl;
	d.PureVirtualFunc();
}


int main(int argc, char** argv)
{
	cout << "main - start \n" << endl;

	sortedArrAndNumberQuestion();

	cout << "\n \n main - end \n" << endl;
	return 0;
}
