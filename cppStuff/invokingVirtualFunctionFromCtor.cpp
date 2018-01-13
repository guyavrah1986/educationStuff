

#include <iostream>

using namespace std;


class A
{
	public:
		A()
		{
			cout << "A::A" << endl;
		}

		virtual void foo()
		{
			cout << "A::foo" << endl;
		}	
};

class B : public A
{
	public:
		B()
		{
			cout << "B::B" << endl;
		}

		virtual void foo()
		{
			cout << "B::foo" << endl;
		}
};

class C : public B
{
	public:
		C()
		{
			cout << "C::C" << endl;
			foo();
		}

		virtual void foo()
		{
			cout << "C::foo" << endl;
		}
};


int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	C c;

	cout << "main - end" << endl;
	return 0;
}


