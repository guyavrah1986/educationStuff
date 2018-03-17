#pragma once

// forward declration
class CLib1;

class CLib2
{
public:
	CLib2();
	~CLib2();

private:
	CLib1& m_lib1Obj;
};