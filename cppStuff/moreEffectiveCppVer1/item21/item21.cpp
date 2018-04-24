// ========================================================================================================================================================================
/*
* Item 21:
* --------
* When we perfrom some operation that requires implict type copnversion for it to succeseed - we face the overhead of creating (and
* later destroying) temporary objects to "fulfill" the conversion task. 
* In order to AVIOD this overhead, when it is possible, we can overload certain functions/operators according to our needs.
* 1) To aviod temporary in the case of UpInt + UpInt we defined this flavour of the operator+
* 2) To aviod temporary in the case of UpInt + int we defined this flavour of the operator+
* 3) To aviod temporary in the case of int + UpInt we defined this flavour of the operator+
*    NOTE: Comment any of the two last flavours (2 OR 3) and see for yourself, that before (and in addition) to the call
*    to the operator, we first invoke the ctor to create the temporary obejct due to the type conversion.
* 4) IMPORTANT: It is an error to ALSO define this flavour of the operator+ for our class. When we perfrom operator overloading
*    it is a rule that at least one of the arguments is a user-defined type, otherwise - it is prohibited !!!
*
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* Key note: Avoid potential creation of temporary objects by eliminating the possibility that an implict type conversion will
*           take place. 
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
*
*/
// ======================================================================================================================================================================

#include <iostream>

using namespace std;

class UpInt 
{
	public:
	UpInt() 
		: m_int(0)
	{	
		cout << "UpInt::UpInt(default) - setting m_int to:" << m_int << " at address:" << this << endl;
	}

	UpInt(int val) 
		: m_int(val)
	{
		cout << "UpInt::UpInt - setting m_int to:" << m_int << " at address:" << this << endl; 
	}

	~UpInt()
	{
		cout << "UpInt::~UpInt - m_int:" << m_int << " at address:" << this << endl;
	}
	
	friend const UpInt operator+(const UpInt& lhs, const UpInt& rhs);	// 1) 
	friend const UpInt operator+(const UpInt& lhs, int rhs);	// 2)
	//friend const UpInt operator+(int lhs, const UpInt& rhs);	// 3)
	//friend const UpInt operator+(int lhs, int rhs);	// 4)

	int m_int;
};

const UpInt operator+(const UpInt& lhs, const UpInt& rhs)
{
	cout << "operator+(const UpInt& lhs, const UpInt& rhs)" << endl;
	return UpInt(lhs.m_int + rhs.m_int);
}

const UpInt operator+(const UpInt& lhs, int rhs)
{
	cout << "operator+(const UpInt& lhs, int rhs)" << endl;
	return UpInt(lhs.m_int + rhs);
}

/*
const UpInt operator+(int lhs, const UpInt& rhs)
{
	cout << "operator+(int lhs, const UpInt& rhs)" << endl;
	return UpInt(lhs + rhs.m_int);
}
*/
void item21Usage()
{
	cout << "item21Usage - start" << endl;
	cout << "item21Usage - creating two UpInt objects on the function's stack" << endl;
	UpInt ui1(1), ui2(2);

	cout << "\n \n item21Usage - adding two UpInt obejets" << endl;
	UpInt ui3 = ui1 + ui2;	// 1)
	cout << "item21Usage - ui3 address is:" << &ui3 << endl;
	
	cout << "\n \n item21Usage - adding ui3 + 7" << endl;
	UpInt ui4 = ui3 + 7;	// 2)
	cout << "item21Usage - ui4 address is:" << &ui4 << endl;

	cout << "\n \n item21Usage - adding 9+ ui2" << endl;
	UpInt ui5 = 9 + ui2;	// 3)
	cout << "item21Usage - ui5 address is:" << &ui5 << endl;

	cout << "\n \n item21Usage - end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	item21Usage();
	
	char c;
	cout << "\n \n main - enter any key and press ENTER to terminate" << endl;
	cin >> c;
	return 0;
}
