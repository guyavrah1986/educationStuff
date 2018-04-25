#include <iostream>
#include <vector>

#include "vector1Exaplained.h"
#include "MyObj.h"
#include "MyObjNoDefualtCtor.h"

using namespace std;

ostream& operator<<(ostream& out, const MyObjNoDefualtCtor& obj)
{
	cout << "MyObjNoDefualtCtor (" << &obj << "," << obj.m_a << ")" << endl;
	return out;
}

ostream& operator<<(ostream& out, const MyObj& obj)
{
	cout << "MyObj (" << &obj << "," << obj.m_a << ")" << endl;
	return out;
}

// ===================================================================================================================================================================
// ===================================================================================================================================================================
// 1) Vector decleration and element access.
// Key note: Accessing an element in a vecotr via vec.at(index) has bounds checking (an exception might be thrown) while
//           vec[index] DOES NOT have.
// ===================================================================================================================================================================
// ===================================================================================================================================================================
/*
 * 1) This example illustrates the difference (and benefits) when using vector (for int in this case) over the use of good old "C style" array of int's.
 * a) The declaration of the static (automatic - on the stack) std::vector can take a NON CONST value (vecSize = 5 in this case).
 * b) The std::vector is cleared automatically once it is "out of scope" -- no need to call the delete method explicitly.
 * c) It is possible to use the "C style" array like access syntax - YET for performance considerations the index is not checked to verify it is
 * in bounds..
 * d) It is also possible to access an element in a vector using the vec.at(index) method. In this case, bounds checking is taking place and upon
 *    an access violation an exception in thrown.
*/
void illustrateVectorDeclerationAndElementsAccess()
{
	cout << "illustrateVectorDeclerationAndElementsAccess - start" << endl;
	// a)
	size_t vecSize = 5;
	vector<int> vec(vecSize);

	for (int i = 0; i < vec.size(); ++i)
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
	catch (const exception& e)
	{
		cout << "illustrateVectorDeclerationAndElementsAccess - caught exception when trying to access vec.at(" << index << ") which is not"
				" in the vector range:" << e.what() << endl;
	}

	cout << "illustrateVectorDeclerationAndElementsAccess - end" << endl;
} // b)

// ===================================================================================================================================================================
// ===================================================================================================================================================================
// 2) Vector size and capacity explained.
// Key note: - Almost always prefer to declare a vector like so (given that the initial size for it is known):
//           vector<T> vec;
//           vec.reserve(initialSize);
//           - Once a vector reaches its full capacity - it will "increase itself" (usually in a factor of 2).
// ===================================================================================================================================================================
// ===================================================================================================================================================================
/*
 * 2) This function illustrate the different approaches on how to declare a vector - with focus on its size.
 * a) This declaration will create an EMPTY vector of int's initialized to their default value (0 in this case).
 * b) After adding an additional element to the vector --> the vector (automatically) will increase its size (double it). The space "left" until
 *    the next growth of the vector is when it will fill all its unused space (capacity - size). Basically this is (capacity - size) is the available
 *    space in every moment.
 * c) This declaration will create a vector of int's with size and capacity of vec2InitialSize. All int's will be initialized to their default value (0).
 * d) As in the first example, in this case as well, the vector will be with size 0 and capacity 0 as well.
 *    NOTE: Different implementation of the STL might implement it differently --> thus causing the default Ctor of vector to initialize it with a certain
 *    size (although we used the default Ctor explicitly).
 * e) As in the case of the int's vector, if we declare the vector with the initial size in the Ctor --> the default Ctor of the object type will be
 *    called ("size" times - as the number of elements we initialed the vector with).
 * f) When we reach the end of the function, due to the fact that the vec4 was declared automatically (on the stack), its Dtor will be invoked.
 *    NOTE:This will cause the invocation of each objet's Dtor within vec4 as well.
 * g) If the object that is contained within the vector has no default Ctor -- then declaring a vector of its type without explicitly initialize the
 *    elements of the vector is not possible.
 * h) Declaring an empty array of this type is possible.Also, combining the usage (directly after the declaration) of the reserve method, is basically
 *    the best practice of how to create a vector (assuming we know in advance, more or less, the desired size of it), and we DO NOT
 *    wish to autoamtically invoke (perhapse for no reason) the default ctor of the objects that will reside in the vector.
 */
void illustrateFillVectorWithObjects()
{
	cout << "illustrateFillVectorWithObjects - start" << endl;

	// a)
	vector<int> vec1;
	cout << "illustrateFillVectorWithObjects - the initial size of vec1 is:" << vec1.size()
			<< " and its capacity is:" << vec1.capacity() << endl;

	// b)
	int firstValToAdd = 17;
	vec1.push_back(firstValToAdd);
	cout << "illustrateFillVectorWithObjects - after adding the first value to vec1 its size is:" << vec1.size()
		<< " and its capacity is:" << vec1.capacity() << endl;

	// c)
	const size_t vec2InitialSize = 5;
	vector<int> vec2(vec2InitialSize);
	cout << "illustrateFillVectorWithObjects - the initial size of vec2 is:" << vec2.size()
			<< " and its capacity is:" << vec2.capacity() << endl;
	cout << "illustrateFillVectorWithObjects - the initial values of the integers in vec2 are:" << endl;
	for (size_t i = 0; i < vec2.size(); ++i)
	{
		cout << "vec2[" << i << "]:" << vec2[i] << endl;
	}


	vec2.push_back(firstValToAdd);
	cout << "illustrateFillVectorWithObjects - after adding the first value to vec2 its size is:" << vec2.size()
			<< " and its capacity is:" << vec2.capacity() << endl;

	// d)
	vector<MyObj> vec3;
	cout << "illustrateFillVectorWithObjects - the initial size of vec3 is:" << vec3.size()
			<< " and its capacity is:" << vec3.capacity() << endl;

	// e)
	size_t sizeOfVec4 = 4;
	vector<MyObj> vec4(sizeOfVec4);
	cout << "illustrateFillVectorWithObjects - the initial size of vec4 is:" << vec4.size()
			<< " and its capacity is:" << vec4.capacity() << endl;
	cout << "illustrateFillVectorWithObjects - displaying elements in vec4:" << endl;
	for (size_t i = 0; i < vec4.size(); ++i)
	{
		cout << "vec4[" << i << "]:" << vec4[i] << endl;
	}

	// g)
	//vector<MyObjNoDefualtCtor> vec5(3);

	// h)
	size_t sizeOfVec5 = 4;
	vector<MyObjNoDefualtCtor> vec5;
	vec5.reserve(sizeOfVec5);
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

	cout << "\n \n illustrateFillVectorWithObjects - displaying elements in vec5:" << endl;
	for (size_t i = 0; i < vec5.capacity(); ++i)
	{
		try
		{
			cout << "vec5[" << i << "]:" << vec5.at(i) << endl;
		}
		catch (const out_of_range& e)
		{
			cout << "illustrateFillVectorWithObjects - caught an exception when"
				" trying to access vec[" << i << "]:" << e.what() << endl;
		}
	}

	cout << "illustrateFillVectorWithObjects - end \n \n";
} // f)

// ===================================================================================================================================================================
// ===================================================================================================================================================================
// 3) Illustrates the high level detailes of how reserve SHOULD be used, and the capacity Vs size parameters of std::vector.
// Key note: - When using reserve, we are only allocating enough "room" for the desired amount of elements, NOTHING more.
//           - At any given time, the number of elements we can add to the vector WITHOUT triggering a "resize" is defined 
//             to be = vec.capacity() - vec.size().
// ===================================================================================================================================================================
// ===================================================================================================================================================================
/*
 * 3) This example illustrate how the vector is growing when we insert elements into it.
 * a) The most "common" (and naive) manner to insert elements into the vector. Note that for each element (MyObj) that is inserted,
 *    two ctor's are invoked: The regular ctor that builds the temporary object (which later immediatly is being destructed), followed
*     by the copy ctor that actually inserts a COPY of the "original" (temporary) object into the vector.
*     It is the copy that will finally reside within the vector.
 * b) Same thing goes here as well: When adding the fourth element, two ctor's will be called.The more important notation here, is that due to the
 *    fact that we reached the vector capacity --> we will have to increase the vector size (the vector will do it for us off course), causing
 *    the capacity of the vector to increase by a factor of two (3 X 2 = 6) --> YET the last two elements WONT be initialized.
 *    So, after the fourth element is inserted, the first three elements will be copied into the "new" locations in the extented
 *    vector.
 *    Implicitly using the copy ctor --> so accessing them is undefined !!
 * c) In this example we use the C++11 feature of "move semantics" by inserting (adding) the elements to the vector using the emplace_back() method.
 *    In this case, the "flow" is as follows:
 *    - A temporary object is constructed via the "regular" ctor.
 *    - It is being "moved" to a different object using the "move copy ctor", i.e.- a "new" object is created and the contents (state) of the previous
 *      object are being moved (NOT copied as a good copy ctor would have done) into the state of the newly created object.
 *    - A destructor is called for the first object that was created.
 * d) IMPORTANT NOTE: When using reserve with some value, say 3, and then we add less than this ammount, say only 2 elements (user
 *    defined objects) into the vector, if we try to access the element(s) in the indecies that WERE not initiazlied - we will get
 *   an exception - reserve DOES NOT initialize the all the "n" elements its reserves room for - it ONLY (as it name states) reserves
 *   room for them, so it is undefined behaviour to access them at that point.
 */
void illustrateVectorGrowth()
{
	cout << "illustrateVectorGrowth - start" << endl;
	size_t initialCapacity = 3;
	vector<MyObj> vec1;
	vec1.reserve(initialCapacity);
	
	// a)
	cout << " \n \n \n illustrateVectorGrowth - inserting  elements into vec1:" << endl;
	for (int i = 0; i < initialCapacity; ++i)
	{
		vec1.push_back(MyObj(i + 1));
	}

	cout << "\n \n illustrateVectorGrowth - displaying elements in vec1:" << endl;
	for (size_t i = 0; i < vec1.capacity(); ++i)
	{
		cout << "vec1[" << i << "]:" << vec1[i] << endl;
	}

	// b)
	cout << "\n \n illustrateVectorGrowth - now, insert the" << initialCapacity + 1 << " element into vec1:" << endl;
	vec1.push_back(MyObj(static_cast<int>(initialCapacity) + 1));
	cout << "illustrateVectorGrowth - after adding the " << initialCapacity + 1 << " element into the "
		" vector, its capacity is now:" << vec1.capacity() << endl;
	cout << "illustrateVectorGrowth - displaying elements in vec1 (after adding the"
		<< initialCapacity + 1 << " element before):" << endl;
	for (size_t i = 0; i < vec1.capacity(); ++i)
	{
		try
		{
			cout << "vec1[" << i << "]:" << vec1.at(i) << endl;
		}
		catch (const out_of_range& e)
		{
			cout << "illustrateVectorGrowth - trying to access vec1[" << i << "], which has not been initialized"
				" correctly:" << e.what() << endl;
		}
	}

	// c)
	vector<MyObj> vec2;
	initialCapacity = 3;
	vec2.reserve(initialCapacity);
	cout << " \n \n \n illustrateVectorGrowth - inserting  elements into vec2 using the C++11 emplace_back method:" << endl;
	for (int i = 0; i < initialCapacity; ++i)
	{
		vec2.emplace_back(MyObj(i + 1));
	}

	cout << "illustrateVectorGrowth - displaying elements in vec2:" << endl;
	for (size_t i = 0; i < vec2.capacity(); ++i)
	{
		cout << "vec2[" << i << "]:" << vec2[i] << endl;
	}

	// d)
	vector<MyObj> vec3;
	vec3.reserve(initialCapacity);
	vec3.push_back(MyObj(13));
	for (size_t i = 0; i < vec3.capacity(); ++i)
	{
		try
		{
			cout << "illustrateVectorGrowth - vec3[" << i << "]:" << vec3.at(i) << endl;
		}
		catch (const out_of_range& e)
		{
			cout << "illustrateVectorGrowth - trying to access vec3[" << i << "], which has not been initialized"
				" correctly:" << e.what() << endl;
		}
	}
}
