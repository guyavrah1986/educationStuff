#include <iostream>
#include <vector>
#include <algorithm>

#include "vector2Exaplained.h"
#include "MyObj.h"
#include "MyObjNoDefualtCtor.h"

using namespace std;

template <typename T> void printVec(const vector<T>& vec)
{
	for (size_t i = 0; i < vec.size(); ++i)
	{
		cout << vec[i] << " ";
	}
	cout << endl;
}

// ===================================================================================================================================================================
// ===================================================================================================================================================================
// 1) Here we will describe the basic of iterators regarding vectors.
// Key note: const_iterator will get a const reference to the vector's element, so in case we are not modifying the vector
//           it is the predered way to traverse it.
// ===================================================================================================================================================================
// ===================================================================================================================================================================
/*
* 1) 
* a) This is the good old "C style" way to traverse a vector.Remember, that under the hood it simply stores its elements 
*    in a continuous block of memory, so "playing" with their addresses is fair legal.
* b) In the more "C++ STL" generic way, it is also possible, and prefered, to traverse the vector like this.
*    Note that we used const_iterator cause we DO NOT intend to modify the vector's elements.If we do, we will need to use
*    the "normal" iterator, vector<doubel>::iterator.
*/
void illustrateVectorIterator()
{
	cout << "illustrateVectorIterator - start" << endl;
	vector<double> vec1 = { 1.2, 4.8, 90.8 };

	// a) 
	const double* pd = &vec1[0];
	cout << "illustrateVectorIterator - displating vec1 elements using double*" << endl;
	for (size_t i = 0; pd < (&vec1[0] + vec1.capacity()); ++pd)
	{
		cout << "illustrateVectorIterator - vec1[" << i << "]:" << *pd << endl;
	}

	// b)
	vector<double>::const_iterator it = vec1.begin();
	cout << "illustrateVectorIterator - displating vec1 elements const_iterator" << endl;
	for (size_t i = 0; it != vec1.end(); ++it, ++i)
	{
		cout << "illustrateVectorIterator - vec1[" << i << "]:" << *it << endl;
	}
}

// ===================================================================================================================================================================
// ===================================================================================================================================================================
// 2) 
// Key note: Always prefer to use the STL methods to remove and erase elements from a vector (or any other STL container which
//           is applicable for this task).
// ===================================================================================================================================================================
// ===================================================================================================================================================================
/*
* 2) 
* a) The use in both of the method COMBINED will erase ALL occurences of the value to remove form the given vector. Note that
*    in this case it is from a POD vector (int's).
* b) 
*/

void illustrateErasingElementFromVector()
{
	cout << "illustrateErasingElementFromVector - start" << endl;
	
	// a)
	int valToRemove1 = 3;
	int valToRemove2 = 4;
	vector<int> vec2 = { 1,2,3,4,5,4,6,7,2 };
	cout << "illustrateErasingElementFromVector - before removing " << valToRemove1 << " which"
		" occurs " << 1 << " times in the vec2:" << endl;
	printVec(vec2);
	vec2.erase(remove(vec2.begin(), vec2.end(), valToRemove1), vec2.end());

	cout << "\n \n illustrateErasingElementFromVector - after removing " << valToRemove1 << " which"
		" occurs" << 1 << " time in the vec2:" << endl;
	printVec(vec2);

	vec2.erase(remove(vec2.begin(), vec2.end(), valToRemove2), vec2.end());
	cout << "\n \n illustrateErasingElementFromVector - after removing " << valToRemove2 << " which"
		" occurs " << 2 << " time in the vec2:" << endl;
	printVec(vec2);
	
	vector<MyObj> vec1;
	const size_t size = 5;
	int valToRemove = 2;
	vec1.reserve(size);
	for (size_t i = 0; i < vec1.capacity(); ++i)
	{
		vec1.emplace_back(MyObj(static_cast<int>(i) + 1));
	}

	cout << "illustrateErasingElementFromVector - vec1 size is:" << vec1.size() << " and"
		" vec1 capacity is:" << vec1.capacity() << endl;

	// b)
	vector<MyObj>::iterator it = vec1.begin();
	while (it != vec1.end())
	{
		if ((*it).m_a == valToRemove)
		{
			cout << "illustrateErasingElementFromVector - found an element with the value to"
				" erase:" << valToRemove << endl;
			it = vec1.erase(it);
		}
		else
		{
			cout << "illustrateErasingElementFromVector - we are NOT erasing element with"
				" value:" << (*it).m_a << endl;
			++it;
		}
	}

	cout << "illustrateErasingElementFromVector - after erasing the value to remove:" << valToRemove << " vec1"
		" is:" << endl;
	printVec(vec1);
	cout << "illustrateErasingElementFromVector - end" << endl;
}