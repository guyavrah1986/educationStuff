
class Base
{
public:
	Base();
	virtual ~Base();

	virtual void pureVirtualFunc1() = 0;
	virtual bool pureVirtualFunc2() const = 0;

};
