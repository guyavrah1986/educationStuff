#include "baseClassWithPureVirtualFunctions.h"

class Derived : public Base
{
public:
	Derived();
	virtual ~Derived();

	virtual void pureVirtualFunc1() override;
	virtual bool pureVirtualFunc2() const override;

};
