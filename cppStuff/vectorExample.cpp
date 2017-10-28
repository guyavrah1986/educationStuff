// ===================================================================================================================================================================
// ===================================================================================================================================================================
//
// std::vector of the STL:
// ----------------------
// This short tutorial describes some important aspects that needs to be considered when using the STL contaniers. In this specific case the examples will be depicts 
// with the std::vector container.
// 
// ===================================================================================================================================================================
// ===================================================================================================================================================================


#include <iostream>
#include <vector>


class MyObj
{

public:
	MyObj(int a) : m_a(a) 
	{
		std::cout <<"MyObj::MyObj - setting m_a to:" << m_a << " this address is:" << this << std::endl;
	}

	MyObj() : m_a(17)
	{
		std::cout << "MyObj::MyObj (defualt) - setting m_a to:" << m_a << " this address is:" << this << std::endl;
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

	std::cout << "main - start" << std::endl;
	
	fillVectorWithObjects();
	
	std::cout << "main - end" << std::endl;
	return 0;
}

