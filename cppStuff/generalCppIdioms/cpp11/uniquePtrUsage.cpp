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
//    unique_ptr from the function to the unique_ptr that receives it (remeber that copy semantics are disabled for std::unique_ptr).
// 6) When passing an std::unique_ptr to a function by value, the caller "loses" ownership on the pointer - i.e.- when the fucntion will return, the std::unique_ptr
//    will no longer be valid anymore. Also note that, yopu MUST use std::move in order to pass the std::unique_ptr by value to the callee function.
// 
// ===================================================================================================================================================================
// ===================================================================================================================================================================

#include <iostream>
#include <memory> 	// for std::unique_ptr and std::make_unique
#include <utility>	// for std::move

using namespace std;

class MyObj
{
public:
	MyObj() { cout << "MyObj::MyObj" << endl; }
	~MyObj() { cout << "MyObj::~MyObj" << endl; }
	friend std::ostream& operator<<(std::ostream& out, const MyObj &myObj)
	{
		out << "MyObj::operator<<" << endl;
		return out;
	}
};

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

void passUniquePtrToFuncByVal(unique_ptr<MyObj> upMyObj)
{
	cout << "passUniquePtrToFuncByVal - MyObj is:" << *upMyObj << endl;
}

// ===================================================================================================================================================================
// ===================================================================================================================================================================
// main
// ===================================================================================================================================================================
// ===================================================================================================================================================================

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	illustrateUniquePtrMoveSemantics();
	unique_ptr<string> up1 = getString();
	cout << "main - we got the string:" << (*up1) << " (from getString method)" << endl;

	{	// 6)
		cout << "main - start of dummy scope, creating a MyObj unique_ptr (along with an object)" << endl;
		auto up2 = make_unique<MyObj>();
		passUniquePtrToFuncByVal(move(up2));

		if (up2)
		{
			cout << *up2 << endl;
		}
		else
		{
			cout << "main - back in dummy scope, up2 is NULL" << endl;
		}

		cout << "main - end of dummy scope" << endl;
	}
		
	cout << "main - end" << endl;
	return 0;
}
