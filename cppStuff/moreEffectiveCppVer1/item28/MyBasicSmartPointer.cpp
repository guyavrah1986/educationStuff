#include <iostream>
#include "MyBasicSmartPointer.h"

using namespace std;

template <class PointeeType>
MyBasicSmartPointer<PointeeType>::MyBasicSmartPointer(PointeeType* pointee)
	: m_pointee(pointee)
{
	cout << "MyBasicSmartPointer::MyBasicSmartPointer - setting m_pointee to point to:"
		<< m_pointee << " this address is:" << this << endl;
}

template <class PointeeType>
MyBasicSmartPointer<PointeeType>::MyBasicSmartPointer(const MyBasicSmartPointer& other)
{
	cout << "MyBasicSmartPointer::MyBasicSmartPointer(copy) - setting m_pointee to point to:"
		<< other.m_pointee << " this address is:" << this << " (other address is:" << &other << ")" << endl;
	this->m_pointee = other.m_pointee;
	//other.m_pointee = 0;
}
	
template <class PointeeType>
MyBasicSmartPointer<PointeeType>& MyBasicSmartPointer<PointeeType>::operator=(const MyBasicSmartPointer& rhs)
{
	cout << "MyBasicSmartPointer::operator= - setting m_pointee to point to:"
		<< rhs.m_pointee << " this address is:" << this << " (rhs address is:" << &rhs << ")" << endl;
	if (this == &rhs)
	{
		cout << "MyBasicSmartPointer::operator= - self assgining, returning this" << endl;
		return *this;
	}

	this->m_pointee = rhs.m_pointee;
	//rhs.m_pointee = 0;
	return *this;
}

template <class PointeeType>
MyBasicSmartPointer<PointeeType>::~MyBasicSmartPointer()
{
	cout << "MyBasicSmartPointer::~MyBasicSmartPointer - m_pointee to point to:"
		<< this->m_pointee << " this address is:" << this << endl;
	delete this->m_pointee;
}


template <class PointeeType>
PointeeType* MyBasicSmartPointer<PointeeType>::operator->() const
{
	cout << "MyBasicSmartPointer::operator-> - returning m_pointee address:" << this->m_pointee << endl;
	return this->m_pointee;
}

template <class PointeeType>
PointeeType& MyBasicSmartPointer<PointeeType>::operator*() const
{
	cout << "MyBasicSmartPointer::operator* - returning m_pointee address:" << this->m_pointee << endl;
	return *(this->m_pointee);
}

// In order to be able to "split" the implementation "out from" the header file, 
// and put it here.
template class MyBasicSmartPointer<int>;
