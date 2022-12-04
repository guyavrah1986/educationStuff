#include <iostream>
#include <string>


// 1) This is the interface all the different decorators will implement - each one of them will "add" it 
//    logic to the basic one.
class IHandlePacket
{
	public:
	virtual void HandlePacket(const std::string& packet) = 0;
	virtual ~IHandlePacket() 
	{
		std::cout << "IHandlePacket::~IHandlePacket" << std::endl;
	}
};

// 2) This is the most basic and "must" (common to all) logic. 
class BasicHandlePacket : public IHandlePacket
{
	public:
	BasicHandlePacket()
	{
		std::cout << "BasicHandlePacket::BasicHandlePacket" << std::endl;
	}
	
	virtual ~BasicHandlePacket()
	{
		std::cout << "BasicHandlePacket::~BasicHandlePacket" << std::endl;
	}

	virtual void HandlePacket(const std::string& packet)
	{
		std::cout << "BasicHandlePacket::HandlePacket" << std::endl;
	}
};

// 3) The DECORATOR definition
class Decorator : public IHandlePacket
{
	public:
	Decorator(IHandlePacket& decorator) : m_decorator(decorator)
	{
		std::cout << "Decorator::Decorator" << std::endl;
	}

	virtual ~Decorator()
	{
		std::cout << "Decorator::~Decorator" << std::endl;
	}

	virtual void HandlePacket(const std::string& packet)
	{
		std::cout << "Decorator::HandlePacket" << std::endl;
		m_decorator.HandlePacket(packet);
	}

	protected:
	IHandlePacket& m_decorator;
};

// 4) A concrete decorator example
class HandlePacketLayer5 : public Decorator
{
	public:
	HandlePacketLayer5(IHandlePacket& decorator) : Decorator(decorator)
	{
		std::cout << "HandlePacketLayer5::HandlePacketLayer5" << std::endl;
	}

	virtual ~HandlePacketLayer5()
	{
		std::cout << "HandlePacketLayer5::~HandlePacketLayer5" << std::endl;
	}

	virtual void HandlePacket(const std::string& packet)
	{
		std::cout << "HandlePacketLayer5::HandlePacket" << std::endl;
		m_decorator.HandlePacket(packet);
		std::cout << "HandlePacketLayer5::HandlePacket - now adding our specific logic on top of the basic logic..." << std::endl;
	}
};

// 5) A concrete decorator example
class HandlePacketLayer4 : public Decorator
{
	public:
	HandlePacketLayer4(IHandlePacket& decorator) : Decorator(decorator)
	{
		std::cout << "HandlePacketLayer4::HandlePacketLayer4" << std::endl;
	}

	virtual ~HandlePacketLayer4()
	{
		std::cout << "HandlePacketLayer4::~HandlePacketLayer4" << std::endl;
	}

	virtual void HandlePacket(const std::string& packet)
	{
		std::cout << "HandlePacketLayer4::HandlePacket" << std::endl;
		m_decorator.HandlePacket(packet);
		std::cout << "HandlePacketLayer4::HandlePacket - now adding our specific logic on top of the basic logic..." << std::endl;
	}
};

// 6) A concrete decorator example
class HandlePacketLayer3 : public Decorator
{
	public:
	HandlePacketLayer3(IHandlePacket& decorator) : Decorator(decorator)
	{
		std::cout << "HandlePacketLayer3::HandlePacketLayer3" << std::endl;
	}

	virtual ~HandlePacketLayer3()
	{
		std::cout << "HandlePacketLayer3::~HandlePacketLayer3" << std::endl;
	}

	virtual void HandlePacket(const std::string& packet)
	{
		std::cout << "HandlePacketLayer3::HandlePacket" << std::endl;
		m_decorator.HandlePacket(packet);
		std::cout << "HandlePacketLayer3::HandlePacket - now adding our specific logic on top of the basic logic..." << std::endl;
	}
};

void decoratorExample()
{
	std::cout << "decoratorExample - start" << std::endl;
	BasicHandlePacket baseHandler;
	
	HandlePacketLayer5 extraHandler5(baseHandler);
	HandlePacketLayer4 extraHandler4(extraHandler5);
	HandlePacketLayer3 extraHandler3(extraHandler4);

	extraHandler3.HandlePacket("packet to analyze");
	
	std::cout << "decoratorExample - end" << std::endl;
}


