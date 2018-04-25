#include <iostream>
#include <vector>

#include "vector2Exaplained.h"
#include "MyObj.h"
#include "MyObjNoDefualtCtor.h"

using namespace std;

// ===================================================================================================================================================================
// ===================================================================================================================================================================
// 1) Here we will describe the basic of iterators regarding vectors.
// Key note:
// ===================================================================================================================================================================
// ===================================================================================================================================================================
/*
* 1) 
* a) This is the good old "C style" way to traverse a vector.Remember, that under the hood it simply stores its elements 
*    in a continuous block of memory, so "playing" with their addresses is fair legal.
* b) In the more "C++ STL" generic way, it is also possible, and prefered, to traverse the vector like this.
*    Note that we used const_iterator cause we DO NOT intend to modify the vector's elements.If we do, we will need to use
*    the "normal" iterator, vector<doubel>::iterator.
*
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