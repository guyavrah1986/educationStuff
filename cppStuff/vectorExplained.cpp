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

class MyObjNoDefualtCtor
{
public:
	MyObjNoDefualtCtor(int a) : m_a(a)
	{
		cout << "MyObjNoDefualtCtor::MyObjNoDefualtCtor - setting m_a to:" << m_a << endl;
	}

	MyObjNoDefualtCtor(const MyObjNoDefualtCtor& other) : m_a(other.m_a)
	{
		cout << "MyObjNoDefualtCtor::copy_ctor - setting m_a to:" << m_a << endl;
	}

	~MyObjNoDefualtCtor()
	{
		cout << "MyObjNoDefualtCtor::~MyObjNoDefualtCtor - address is" << this << endl;
	}

	MyObjNoDefualtCtor() = delete;

	friend ostream& operator<<(ostream& out, const MyObjNoDefualtCtor& obj);
	int m_a;
};

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

ostream& operator<<(ostream& out, const MyObj& obj)
{
	cout << "MyObj (" << &obj << "," << obj.m_a << ")" << endl;
	return out;
}

ostream& operator<<(ostream& out, const MyObjNoDefualtCtor& obj)
{
	cout << "MyObjNoDefualtCtor (" << &obj << "," << obj.m_a << ")" << endl;
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
 * d) It is also possible to access an element in a vector using the vec.at(index) method. In this case, bounds checking is taking place and upon
 *    an access violation an exception in thrown.
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
	catch (exception& e)
	{
		cout << "illustrateVectorDeclerationAndElementsAccess - caught exception when trying to access vec.at(" << index << ") which is not"
				" in the vector range" << endl;
	}

	cout << "illustrateVectorDeclerationAndElementsAccess - end" << endl;
} // b)

/*
 * 2) This function illustrate the different approaches on how to declare a vector - with focus on its size.
 * a) This declaration will create an empty vector of int's.
 * b) This declaration will create an array of int's with size and capacity of 10. All int's will be initialized to their default value (0).
 * c) After adding an additional element to the vector --> the vector (automatically) will increase its size (double it). The space "left" until
 *    the next growth of the vector is when it will fill all its unused space (capacity - size). Basically this is (capacity - size) is the available
 *    space in every moment.
 * d) As in the first example, in this case as well, the vector will be with size 0 and capacity 0 as well.
 *    NOTE: Different implementation of the STL might implement it differently --> thus causing the default Ctor of vector to initialize it with a certain
 *    size (although we used the default Ctor explicitly).
 * e) As in the case of the int's vector, if we declare the vector with the initial size in the Ctor --> the default Ctor of the object type will be
 *    called ("size" times - as the number of elements we initialed the vector with).
 * f) When we reach the end of the function, due to the fact that the vec4 was declared automatically (on the stack), its Dtor will be invoked.
 *    This will cause the invocation of each objet's Dtor within vec4 as well.
 * g) If the object that is contained within the vector has no default Ctor -- than declaring an array if its type without explicitly initialize the
 *    elements of the vector is not possible.
 * h) Declaring an empty array of this type is possible.Also, combining the usage (directly after the declaration) of the reserve method, is basically
 *    the best practice of how to create a vector (assuming we know in advance, more or less, the desired size of it).
 */
void illustrateFillVectorWithObjects()
{
	cout << "illustrateFillVectorWithObjects - start" << endl;

	// a)
	vector<int> vec1;
	cout << "illustrateFillVectorWithObjects - the initial size of vec1 is:" << vec1.size()
			<< " and its capacity is:" << vec1.capacity() << endl;
	// b)
	vector<int> vec2(10);
	cout << "illustrateFillVectorWithObjects - the initial size of vec2 is:" << vec2.size()
			<< " and its capacity is:" << vec2.capacity() << endl;
	cout << "illustrateFillVectorWithObjects - the initial values of the integers in vec2 are:" << endl;
	for (size_t i = 0; i < vec2.size(); ++i)
	{
		cout << "vec2[" << i << "]:" << vec2[i] << endl;
	}

	// c)
	int firstValToAdd = 17;
	vec1.push_back(firstValToAdd);
	cout << "illustrateFillVectorWithObjects - after adding the first value to vec1 its size is:" << vec1.size()
			<< " and its capacity is:" << vec1.capacity() << endl;

	vec2.push_back(firstValToAdd);
	cout << "illustrateFillVectorWithObjects - after adding the first value to vec2 its size is:" << vec2.size()
			<< " and its capacity is:" << vec2.capacity() << endl;

	// d)
	vector<MyObj> vec3;
	cout << "illustrateFillVectorWithObjects - the initial size of vec3 is:" << vec3.size()
			<< " and its capacity is:" << vec3.capacity() << endl;

	// e)
	vector<MyObj> vec4(4);
	cout << "illustrateFillVectorWithObjects - the initial size of vec4 is:" << vec4.size()
			<< " and its capacity is:" << vec4.capacity() << endl;

	// g)
	//vector<MyObjNoDefualtCtor> vec5(3);

	// h)
	vector<MyObjNoDefualtCtor> vec5;
	vec5.reserve(3);
	cout << "illustrateFillVectorWithObjects - the initial size of vec5 is:" << vec5.size()
			<< " and its capacity is:" << vec5.capacity() << endl;

	MyObjNoDefualtCtor obj1(12);
	MyObjNoDefualtCtor obj2(15);
	MyObjNoDefualtCtor obj3(17);

	// insert them to the vector using "old fashion" (prior to C++11 move semantics)
	cout << "illustrateFillVectorWithObjects - about to push obj1 into the vec5" << endl;
	vec5.push_back(obj1);
	cout << "illustrateFillVectorWithObjects - about to push obj2 into the vec5" << endl;
	vec5.push_back(obj2);
	cout << "illustrateFillVectorWithObjects - about to push obj3 into the vec5" << endl;
	vec5.push_back(obj3);

	cout << "illustrateFillVectorWithObjects - end \n \n";
} // f)


// ===================================================================================================================================================================
// ===================================================================================================================================================================
// main
// ===================================================================================================================================================================
// ===================================================================================================================================================================


int main(int argc, char** argv)
{
	std::cout << "vectorExplained - start" << std::endl;


	// 1)
	// illustrateVectorDeclerationAndElementsAccess();

	// 2)
	illustrateFillVectorWithObjects();

	
	//fillVectorWithObjects();
	
	std::cout << "vectorExplained - end" << std::endl;
	return 0;
}

