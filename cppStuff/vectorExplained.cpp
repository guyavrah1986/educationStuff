// ===================================================================================================================================================================
// ===================================================================================================================================================================
//
// std::vector of the STL:
// ----------------------
// This short tutorial describes some important aspects that needs to be considered when using the STL containers. In this specific case the examples
// will be depicts with the std::vector container.
// 
// ===================================================================================================================================================================
// ===================================================================================================================================================================


#include <iostream>
#include <vector>

using namespace std;

class MyObj
{

public:
	MyObj(int a) : m_a(a) 
	{
		std::cout <<"MyObj::MyObj - setting m_a to:" << m_a << " this address is:" << this << std::endl;
	}

	MyObj() : m_a(17)
	{
		std::cout << "MyObj::MyObj (default) - setting m_a to:" << m_a << " this address is:" << this << std::endl;
	}

	MyObj(const MyObj& other) : MyObj(other.m_a)
	{
		std::cout << "MyObj::MyObj (copy) - setting m_a to:" << m_a << " this address is:" << this << std::endl;
	}

	~MyObj()
	{
		std::cout << "MyObj::~MyObj - this address is:" << this << std::endl;
	}

	MyObj& operator=(const MyObj& rhs)
	{
		std::cout << "MyObj::operator=" << std::endl; 
		if (this == &rhs)
		{
			return *this;
		}

		std::cout << "setting m_a to:" << rhs.m_a << std::endl;
		
		this->m_a = rhs.m_a;

		return *this;
	}

	friend std::ostream& operator<<(const std::ostream& out, const MyObj& obj);
	
	int m_a;
};

std::ostream& operator<<(std::ostream& out, const MyObj& obj)
{
	std::cout << "MyObj (" << &obj << "," << obj.m_a << ")" << std::endl;
	return out;
}

// ===================================================================================================================================================================
// ===================================================================================================================================================================
//
// Usages functions: each function aims to describe a different "topic".
//
// ===================================================================================================================================================================
// ===================================================================================================================================================================

/*
 * 1) This example illustrates the difference (and benefits) when using vector (for int in this case) over the use of good old "C style" array of int's.
 * a) The declaration of the static (automatic - on the stack) std::vector can take a non const value (vecSize = 5 in this case).
 * b) The std::vector is cleared automatically once it is "out of scope" -- no need to call the delete method explicitly.
 * c) It is possible to use the "C style" array like access syntax - YET for performance considerations the index is not checked to verify it is
 * in bounds..
 *
*/

void illustrateVectorDeclerationAndElementsAccess()
{
	cout << "illustrateVectorDeclerationAndElementsAccess - start" << endl;
	// a)
	size_t vecSize = 5;
	vector<int> vec(vecSize);

	for (size_t i = 0; i < vec.size(); ++i)
	{
		vec[i] = i;
		cout << "vec[" << i << "]:" << vec[i] << endl;
	}

	// c)
	size_t index = 4;
	cout << "illustrateVectorDeclerationAndElementsAccess - access vec[" << index << "]" << " gives:" << vec[index] << endl;

	// d)
	try
	{
		index = 5;
		cout << "illustrateVectorDeclerationAndElementsAccess - trying to access element which not in range of the vector with vec.at(" << index <<
				")" << " gives:" << vec.at(index) << endl;
	}
	catch (exception e)
	{
		cout << "illustrateVectorDeclerationAndElementsAccess - caught exception when trying to access vec.at(" << index << ") which is not"
				" in the vector range" << endl;
	}

	cout << "illustrateVectorDeclerationAndElementsAccess - end" << endl;
} // b)

void fillVectorWithObjects()
{
	std::vector<MyObj> vec;

	std::cout << "fillVectorWithObjects::start- about to fill the vecotr with some objects, first lets create three of them:" << std::endl;
	MyObj obj1(12);
	MyObj obj2(15);
	MyObj obj3;

	// insert them to the vector using "old fashion" (prior to C++11 move semantics)
	std::cout << "about to push obj1 into the vector" << std::endl;	
	vec.push_back(obj1);
	std::cout << "about to push obj2 into the vector" << std::endl;
	vec.push_back(obj2);
	std::cout << "about to push obj3 into the vector" << std::endl;
	vec.push_back(obj3);

	std::cout << "fillVectorWithObjects::end \n \n";
}


// ===================================================================================================================================================================
// ===================================================================================================================================================================
// main
// ===================================================================================================================================================================
// ===================================================================================================================================================================


int main(int argc, char** argv)
{

	std::cout << "vectorExplained - start" << std::endl;
	illustrateVectorDeclerationAndElementsAccess();


	
	//fillVectorWithObjects();
	
	std::cout << "vectorExplained - end" << std::endl;
	return 0;
}

