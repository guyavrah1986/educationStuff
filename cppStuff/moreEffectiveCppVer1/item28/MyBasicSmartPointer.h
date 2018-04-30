#pragma once

template <class PointeeType>
class MyBasicSmartPointer
{
public:
	MyBasicSmartPointer(PointeeType* pointee = 0);
	MyBasicSmartPointer(const MyBasicSmartPointer& other);
	MyBasicSmartPointer& operator=(const MyBasicSmartPointer& rhs);
	~MyBasicSmartPointer();
	PointeeType* operator->() const;
	PointeeType& operator*() const;

private:
	PointeeType* m_pointee;

};