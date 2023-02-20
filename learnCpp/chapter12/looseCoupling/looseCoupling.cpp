// ==============================================================================================================================
// ==============================================================================================================================
// Loose coupling:
// --------------
// 1. When a class has a inner class within it, sometimes, it might indicate on "tight coupling". In the first example, the 
//    switch is "too coupled" to the Lamp class (in other words, it is "switchable only" when it contains a Lamp - but this is
//    NOT always the case).
//
// ==============================================================================================================================
// ==============================================================================================================================

#include <iostream>

using namespace std;

class Lamp
{
public:
	explicit Lamp(unsigned int voltage) : m_voltage(voltage) { cout << "Lamp::Lamp - setting m_voltage to:" << m_voltage << endl; }
	virtual ~Lamp() { cout << "Lamp::~Lamp" << endl; }

	void Off() const
	{
		cout << "Lamp::Off" << endl;
	}

	void On() const
	{
		cout << "Lamp::On" << endl;
	}

	unsigned int m_voltage;
};

class SwitchCoupled
{
public:
	explicit SwitchCoupled(const Lamp& lamp) : m_lamp(lamp) {}
	virtual ~SwitchCoupled() {}
	void On() const 
	{
		m_lamp.On();
	}

	void Off() const 
	{
		m_lamp.Off();
	}
	
private:
	const Lamp& m_lamp;
};

class ISwitchable
{
public:
	virtual void On() const = 0;
	virtual void Off() const = 0;
};

class SwitchableLamp : public ISwitchable
{
public:
	explicit SwitchableLamp(unsigned int voltage) : m_voltage(voltage) { cout << "SwitchableLamp::SwitchableLamp - setting m_voltage to:" << m_voltage << endl; }
	virtual ~SwitchableLamp() { cout << "SwitchableLamp::~SwitchableLamp" << endl; }

	virtual void On() const override { cout << "SwitchableLamp::On" << endl; }
	virtual void Off() const override { cout << "SwitchableLamp::Off" << endl; }
private:
	unsigned int m_voltage;
};

class SwitchNotCoupled
{
public:
	explicit SwitchNotCoupled(const ISwitchable& switchable) : m_switchable(switchable) {}
	virtual ~SwitchNotCoupled() {}
	void On() const 
	{
		m_switchable.On();
	}

	void Off() const 
	{
		m_switchable.Off();
	}
	
private:
	const ISwitchable& m_switchable;
};

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	SwitchCoupled switchCoupled(Lamp(50));
	
	SwitchNotCoupled switchNotCoupled(SwitchableLamp(220));
	cout << "main - end" << endl;
	return 0;
}

