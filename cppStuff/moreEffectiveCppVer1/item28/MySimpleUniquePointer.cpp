#include <iostream>
#include "MySimpleUniquePointer.h"

using namespace std;

template <class PointeeType>
MySimpleUniquePointer<PointeeType>::MySimpleUniquePointer(PointeeType* pointee)
	: m_pointee(pointee)
{
	cout << "MySimpleUniquePointer::MySimpleUniquePointer - setting m_pointee to point to:"
		<< m_pointee << " this address is:" << this << endl;
}

template <class PointeeType>
MySimpleUniquePointer<PointeeType>::MySimpleUniquePointer(MySimpleUniquePointer& other)
{
	cout << "MySimpleUniquePointer::MySimpleUniquePointer(copy) - setting m_pointee to point to:"
		<< other.m_pointee << " this address is:" << this << " (other address is:" << &other << ")" << endl;
	this->m_pointee = other.m_pointee;
	other.m_pointee = 0;	// 1b)
}
	
template <class PointeeType>
MySimpleUniquePointer<PointeeType>& MySimpleUniquePointer<PointeeType>::operator=(MySimpleUniquePointer& rhs)
{
	cout << "MySimpleUniquePointer::operator= - setting m_pointee to point to:"
		<< rhs.m_pointee << " this address is:" << this << " (rhs address is:" << &rhs << ")" << endl;
	if (this == &rhs)
	{
		cout << "MySimpleUniquePointer::operator= - self assgining, returning this" << endl;
		return *this;
	}

	delete this->m_pointee;	// 1a)
	this->m_pointee = rhs.m_pointee;
	rhs.m_pointee = 0;	// 1b)
	return *this;
}

template <class PointeeType>
MySimpleUniquePointer<PointeeType>::~MySimpleUniquePointer()
{
	cout << "MySimpleUniquePointer::~MySimpleUniquePointer - m_pointee to point to:"
		<< this->m_pointee << " this address is:" << this << endl;
	delete this->m_pointee;
}


template <class PointeeType>
PointeeType* MySimpleUniquePointer<PointeeType>::operator->() const
{
	cout << "MySimpleUniquePointer::operator-> - returning m_pointee address:" << this->m_pointee << endl;
	return this->m_pointee;
}

template <class PointeeType>
PointeeType& MySimpleUniquePointer<PointeeType>::operator*() const
{
	cout << "MySimpleUniquePointer::operator* - returning m_pointee address:" << this->m_pointee << endl;
	return *(this->m_pointee);
}

// In order to be able to "split" the implementation "out from" the header file, 
// and put it here.
template class MySimpleUniquePointer<int>;
