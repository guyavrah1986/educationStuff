// =============================================================================================================================================================
/*
* item 8:
* ------
* The differences between new operator and operator new.
* 
* 1) When we create a new object (on the heap) using the mentioned statment, what actually happens "under the hood" is two actions:
* a) The new operator allocates "raw memory" in a size that is suffiecnt to hold the allocated object.
* b) The new operator calls the (respective) ctor of the object, WITH the allocated memory from the previous step.
* --> This operator is a BUILT-IN operator of the langudge -- it CAN NOT be modified !!
* 
* 2) The second "function" in this context is the operator new, which is inherintly part of every user defined object.
*    The ONLY task of this function (operator) is to allocate (enough) memory to hold the object in memory. This function CAN be override/overload. 
* a) In case we would have want to add a different "allocation logic" than the "simple" malloc, this function is the place to put it into.
* 
* 3) There are cases (not common) that we DO wish to call the ctor on our own, provided the memory in which the object we are about to create will 
*    reside in - it is very common in cases of shared memory situations.
* a) For this purpose we have a specific "flavour" of the operator new --> placement new. In this flavour, we are ALREADY GIVEN the memory location
*    that will hold the object that is about to be created, THUS, the only thing we have left to do is to invoke "on" this location the (desired) ctor 
*    of the object.
*    NOTE: Other than the buffer in which the object will be created, this fucntion ALSO MUST get all the neccessary arguments for the object.
*
*/
// ================================================================================================================================================================
#include <iostream>

using namespace std;

class B
{
	public:
	B(int a) 
		: m_a(a)
	{
		cout << "B::B - setting m_a to:" << m_a << " this address is:" << this << endl;
	}
	
	virtual ~B()
	{
		cout << "B::~B - this address is:" << this << endl;
	}
	
	void* operator new(size_t size) // 2)
	{
		cout << "B::operator new - got size of:" << size << endl;
		void* ret = malloc(sizeof(char) * size);
		if (ret != NULL)
		{
			cout << "B::operator new - allocated address:" << ret << endl;
		}
		return ret;
	}

	int m_a;
};

B* CreateObjectInBuffer(void* buff, int a)
{
	cout << "CreateObjectInBuffer - got buff in address:" << buff << endl;
	return ::new (buff) B(a);
}

void item8Usage()
{
	cout << "item8Usage - start" << endl;

	// 1)
	B* pb1 = new B(17);
	
	cout << "item8Usage - about to create obejct using placement new, first lets allocate memory for a B object using malloc" << endl;
	void* p = malloc(sizeof(B));
	cout << "item8Usage - allocated memory in address:" << p << endl;
	B* pb2 = CreateObjectInBuffer(p, 8);
	
	cout << "\n \n item8Usage - end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	item8Usage();
	
	
	cout << "main - please enter any key to terminate..." << endl;
	char c;
	cin >> c;
	cout << "\n \n main - end" << endl;
	return 0;
}
