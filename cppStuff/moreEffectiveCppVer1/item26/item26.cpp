// ========================================================================================================================================================================
/*
* Item 26:
* --------
* 1) In case we wish to be able to create a single or zero instances from our class member function, we can use the following
*    approach. It is important to note some points here:
* a) The static instance is within a FUNCTION and not within a class (which might be more intuitive for us). The "extra" 
*    advantage of this approach is that way, the (single) object will be created ONLY if the function that uses it indeed 
*	 will be invoked !! Otherwise - it won't be created at all ("you pay only for what you use").
* b) It is very important NOT to declare the non-member function as inline. That is due to the fact, that if we do so, this
*	 function might have "internal linkage" - which might results in SEVERAL instances for the static object that is defined
*	 withn this function.
*
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* Key notes: - Do NOT create inline non-member functions that contain local static data !!
*			 - Note that, in case that ZeroOrOneInstanceObj class is a base class or contained within another
*			   class, the actual number of instances might NOT be exactly what we wanted or think. 
* 
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
*
*/
// ======================================================================================================================================================================
#define _CRTDBG_MAP_ALLOC  // NOTE: the order of the includes that FOLLOWS this define is important !!!
#include <stdlib.h>  
#include <crtdbg.h> 

#include <iostream>

using namespace std;

namespace someNamespace
{
	class ZeroOrOneInstanceObj
	{
	public:
		void doStuffWithZeroOrOneInstanceObj()
		{
			cout << "ZeroOrOneInstanceObj::doStuffWithZeroOrOneInstanceObj" << endl;
		}

	private:
		ZeroOrOneInstanceObj()
		{
			cout << "ZeroOrOneInstanceObj::ZeroOrOneInstanceObj(default)" << endl;
		}

		ZeroOrOneInstanceObj(const ZeroOrOneInstanceObj& other)
		{
			cout << "ZeroOrOneInstanceObj::ZeroOrOneInstanceObj(copy)" << endl;
		}

		friend ZeroOrOneInstanceObj& theSingleObj();
	};

	/* 1b) inline */ZeroOrOneInstanceObj& theSingleObj()
	{
		static ZeroOrOneInstanceObj obj;	// 1a)
		return obj;
	}
}	// end of namespace someNamespace

void item26Usage()
{
	cout << "item26Usage - start" << endl;
	someNamespace::theSingleObj().doStuffWithZeroOrOneInstanceObj();

	cout << "\n \n item26Usage - end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	item26Usage();
	
	char c;
	cout << "\n \n main - enter any key and press ENTER to terminate" << endl;
	cin >> c;
	_CrtDumpMemoryLeaks();
	return 0;
}
