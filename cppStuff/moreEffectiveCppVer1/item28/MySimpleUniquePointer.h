#pragma once

template <class PointeeType>
class MySimpleUniquePointer
{
public:
	MySimpleUniquePointer(PointeeType* pointee = 0);
	MySimpleUniquePointer(MySimpleUniquePointer& other);
	MySimpleUniquePointer& operator=(MySimpleUniquePointer& rhs);
	~MySimpleUniquePointer();
	PointeeType* operator->() const;
	PointeeType& operator*() const;

private:
	PointeeType* m_pointee;
};