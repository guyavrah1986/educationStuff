#include <iostream>
#include "MyBasicSmartPointer.h"

using namespace std;

template <class PointeeType>
MyBasicSmartPointer<PointeeType>::MyBasicSmartPointer(PointeeType* pointee = 0)
	: m_pointee(pointee)
{
	cout << "MyBasicSmartPointer::MyBasicSmartPointer - setting m_pointee to point to:"
		<< m_pointee << endl;
}

/*
	MyBasicSmartPointer(const MyBasicSmartPointer& other);
	MyBasicSmartPointer& operator=(const MyBasicSmartPointer& rhs);
	~MyBasicSmartPointer();
	PointeeType* operator->() const;
	PointeeType& operator() const;
*/
