// ===================================================================================================================================================================
// ===================================================================================================================================================================
// 1)Object composition:
// ------------------
// Defiend in the following cases:
// a) The container object (parent) contains the part member (child).
// b) The part member is NOT aware of the fact that it is being "contained" within a "larger object".
// c) The container object is responsible for the "lifetime" of the contained object: Usually, when the parent "dies" its child dies as well.
// d) The part (child) member can only belong to a SINGLE parent object -- it can NOT belong to several container objects at the same time.   


// NOTES:
// a) The defualt Ctor of the inner class IS NOT BEING invoked upon a creation of a Container class object (it might be different in other "similar" cases).
// b) Usually, in composition, the parts members will be "normal" members of the container class (locally defined on the stack of the container class).
//
// 2) Object Aggragation:
// ---------------------
// Defined similarly to object composition , but different from it in the following aspects:
// a) The conatiner object IS NOT responsible for the creation NOR the deletion of the aggarate object, for example when the parent class 
//    recived in the Ctor a pointer to an object, and also, it DOES NOT delete this object in non of its functions NOR in the Dtor.
// b) The aggragate object CAN be used in several container objects. 

//
// NOTES:
// a) Usually the aggragte object will be a pointer or a reference to the part object that was created earlier and AS WELL will be destroied later on by another object.
// ===================================================================================================================================================================
// ===================================================================================================================================================================

#include <iostream>
#include <string>

class Inner 
{
	public:
		Inner(int a) : m_a(a)
		{
			std::cout << "Inner::Inner - setting m_a to:" << m_a << std::endl;
		}

		Inner() : m_a(17)
		{
			std::cout << "Inner::Inner (defualt) - setting m_a to:" << m_a << std::endl;
		}

		Inner(const Inner& other)
		{
			this->m_a = other.m_a;
			std::cout << "Inner::Inner (copy) - setting this.m_a to:" << this->m_a << std::endl;
		}

		~Inner()
		{
			std::cout << "Inner::~Inner" << std::endl;
		}

	int m_a;
};


class Container
{
	public:
		Container(int b, const Inner& inner) : m_b(b) , m_inner(inner)
		{
			std::cout << "Container::Container - setting m_b to:" << m_b << " and got inner object with m_a:" << m_inner.m_a << std::endl;
		}

		~Container()
		{
			std::cout << "Container::~Container" << std::endl;
		}

	int m_b;
	Inner m_inner;
};

// This class implies the composition while the contained object is being kept by pointer.
// Note that the container object DOES delete the contained object in its Dtor.
class ContainerByAddress
{

	public:
		ContainerByAddress(int c, const Inner* pInner) : m_c(c), m_inner(pInner)
		{
			std::cout << "ContainerByAddress::ContainerByAddress - setting m_c to:" << m_c << " and got Inner object in the address of" << pInner << std::endl;
		}

		~ContainerByAddress()
		{
			if (m_inner != nullptr)
			{
				delete this->m_inner;
			}
			std::cout << "ContainerByAddress::~ContainerByAddress" << std::endl;
		}

		int m_c;
		const Inner* m_inner;
};




// ===================================================================================================================================================================
// ===================================================================================================================================================================
// main
// ===================================================================================================================================================================
// ===================================================================================================================================================================


int main(int argc, char** argv)
{

	std::cout << "main - start" << std::endl;

	std::cout << "main - creating an Inner object on the main stack" << std::endl;
	Inner inner(12);

	std::cout << "main - creating a Container object on the main stack" << std::endl;
	Container container(13, inner);
	
	
	std::cout << "main - creating an Inner object on the heap" << std::endl;
	Inner* pInner = new Inner(8);	
	ContainerByAddress containerByAddress(45,pInner);

	std::cout << "main - end" << std::endl;
	return 0;
}
