// ===================================================================================================================================================================
// ===================================================================================================================================================================
// 
// std::unique_ptr - usages examples:
// ----------------------------------
// 1) The unique_ptr MUST always be created on the STACK, i.e.- be an automatic variable. This is the only way to be sure that it will be deleted no matter what is 
//    flow of the program.
//
// 2) It implements move semantics - so it is not possible to copy ("share") the pointer.
// 3) It is probably the best type of pointer to return from a factory method.
// 4) In case your compiler is C++14 and on, it is prefered to create a unique_ptr using the std::make_uniuqe method.It is primarly best practice to use it against
//    excpetions issues during object constrcution.
// 5) Returning std::unique_ptr from a function is OK. When it is passed from the calle to the caller - move semantics takes action and passes "ownership" of the 
//    unique_ptr from the function to the unique_ptr that receives it. 
// 
// ===================================================================================================================================================================
// ===================================================================================================================================================================

#include <iostream>
#include <memory> 	// for std::unique_ptr and std::make_unique
#include <utility>	// for std::move

using namespace std;
// ===================================================================================================================================================================
// ===================================================================================================================================================================
// main
// ===================================================================================================================================================================
// ===================================================================================================================================================================

void illustrateUniquePtrMoveSemantics()	// 2)
{
	cout << "illustrateUniquePtrMoveSemantics - start" << endl;
	unique_ptr<int> up1(new int(15));
	unique_ptr<int> up2;

	if (up1)
	{
		cout << "illustrateUniquePtrMoveSemantics - up1 holds:" << (*up1) << endl;
	}
	else
	{
		cout << "illustrateUniquePtrMoveSemantics - up1 is NULL" << endl;
	}

	if (up2)
	{
		cout << "illustrateUniquePtrMoveSemantics - up2 holds:" << (*up2) << endl;
	}
	else
	{
		cout << "illustrateUniquePtrMoveSemantics - up2 is NULL" << endl;
	}

	//up2 = up1; // will not compile !! no copy semantics avaible !!
	up2 = move(up1);
	cout << "illustrateUniquePtrMoveSemantics - performing move" << endl;
	if (up1)
	{
		cout << "illustrateUniquePtrMoveSemantics - up1 holds:" << (*up1) << endl;
	}
	else
	{
		cout << "illustrateUniquePtrMoveSemantics - up1 is NULL" << endl;
	}

	if (up2)
	{
		cout << "illustrateUniquePtrMoveSemantics - up2 holds:" << (*up2) << endl;
	}
	else
	{
		cout << "illustrateUniquePtrMoveSemantics - up2 is NULL" << endl;
	}

	
	cout << "illustrateUniquePtrMoveSemantics - end" << endl;
}

unique_ptr<string> getString()	// 5)
{
	return make_unique<string>("calbas");
}


int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	
	illustrateUniquePtrMoveSemantics();
	unique_ptr<string> up = getString();
	cout << "main - we got the string:" << (*up) << " (from getString method)" << endl;

	cout << "main - end" << endl;
	return 0;
}
