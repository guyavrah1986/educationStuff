#pragma once

#include <iostream>
#include <mutex>

using namespace std;

template <typename T>
class MyStack
{
public:
	MyStack(size_t size) 
		: m_maxSize(size)
		, m_currSize(0)
	{
		cout << "MyStack::MyStack - about to initiated stack with maximum size of:" << m_maxSize << endl;
		m_stackPointer = new T [m_maxSize];
	}

	~MyStack()
	{
		cout << "MyStack::~MyStack" << endl;
		delete [] m_stackPointer;
	}

	// NO COPY
	MyStack(const MyStack& other) = delete; 	 // or make it private prior to C++11 
	MyStack& operator=(const MyStack& rhs) = delete; // or make it private prior to C++11 
	
	/*
	* Pushes elementToPush onto the top of the stack in case there is still space left and returns true.
	* If the stack is already full, element is NOT pushed and the retrun value is false.
	*/
	bool Push(T elementToPush)
	{
		cout << "MyStack::Push - got element:" << elementToPush << " to insert onto the stack" << endl;
		return push(elementToPush);
		
	}

	/*
	* In case the stack is NOT empty and the "place holder" argument provided by the caller is 
	* NOT NULL - the element at the top of the stack is poped into the "place holder" and true is returnd.
	* Otherwise false is returned.
	*/  
	bool Pop(T* popedElement)
	{
		cout << "MyStack::Pop" << endl;
		return pop(popedElement);		
	}

	// for debug
	void DisplayStack()
	{
		cout << "MyStack::DisplayStack - current stack state is:" << endl;
		for (int i = m_currSize - 1; i >= 0; --i)
		{
			cout << m_stackPointer[i] << endl;
		}
	} 

private:
	bool push(T elementToPush)
	{
		cout << "MyStack::push - got element:" << elementToPush << " to insert" << endl;
		lock_guard<mutex> lock(m_mutex);
		if (m_currSize >= m_maxSize)
		{
			cout << "MyStack::push - no space left on stack..." << endl;
			return false;
		}
	
		m_stackPointer[m_currSize++] = elementToPush;
		return true;
	}

	bool pop(T* popedElement)
	{
		cout << "MyStack::pop" << endl;
		lock_guard<mutex> lock(m_mutex);
		if (popedElement == NULL || m_currSize == 0)
		{
			cout << "MyStack::pop - either NULL was provided OR there are no elements on the stack" << endl;
			return false;
		} 	
		
		T tmpVal = m_stackPointer[--m_currSize];
		*popedElement = tmpVal;
		return true;
	}

	// members
	size_t m_maxSize;	// holds the maximum number of elements to holds (i.e.- if it is set to 10, than the valid places are [0 - 9] inclusive)
	size_t m_currSize;	// holds the current availble place (valid values are in the range of [0 - (m_maxSize-1)] inclusive
	T* m_stackPointer;
	mutex m_mutex;
};
