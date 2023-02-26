#pragma once

// forward declration
class CLib1;

class CLib2
{
public:
	explicit CLib2(CLib1& lib1Obj);
	~CLib2();

private:
	CLib1& m_lib1Obj;
};
