// ========================================================================================================================================================================
/*
*
*
*/
// ======================================================================================================================================================================

#include <iostream>

using namespace std;


class A
{
	public:
	A(int a) : m_a(a)
	{
		cout << "A::A - setting m_a to:" << m_a << endl;
	}

	~A()
	{
		cout << "A::~A" << endl;
	}

	
	

};

void item19Usage()
{
	cout << "item19Usage - start" << endl;

	cout << "\n \n item19Usage - " << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;

	cout << "\n \n main - end" << endl;
	return 0;
}

