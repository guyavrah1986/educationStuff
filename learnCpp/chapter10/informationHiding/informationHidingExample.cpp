//================================================================================================================================
//================================================================================================================================
// Information hiding:
// ==================
// 1. Sometimes it is confused with encapsulation - which is NOT the same (encapsulation facilitates information hiding, but does
//    NOT actually mean it is implied.
// 2. Due to the fact that the State enumration is public and the GetState returns a value of one of the enumuration values, it
//    implies "poor information hiding".
// 3. The AutomaticDoorWithGoodInformationHiding illustrate a better approach for information hiding.
//
//
//================================================================================================================================
//================================================================================================================================

#include <iostream>

using namespace std;

class AutomaticDoor
{
public:
	enum State
	{
		open = 0,
		opening,
		closing,
		closed
	};

	explicit AutomaticDoor() : m_state(State::open)
	{
		cout << "AutomaticDoor::AutomaticDoor" << endl;
	}

	virtual ~AutomaticDoor()
	{
		cout << "AutomaticDoor::~AutomaticDoor" << endl;
	}

	State GetState() const
	{
		return m_state;
	}

private:
	State m_state;
	
};

class AutomaticDoorWithGoodInformationHiding
{
public:
	explicit AutomaticDoor() : m_state(State::open)
	{
		cout << "AutomaticDoor::AutomaticDoor" << endl;
	}

	virtual ~AutomaticDoor()
	{
		cout << "AutomaticDoor::~AutomaticDoor" << endl;
	}

	State GetState() const
	{
		return m_state;
	}

	bool IsOpen() const
	{
		return (State::open == m_state);
	}

private:
	enum State
	{
		open = 0,
		opening,
		closing,
		closed
	};

	State m_state;	
};

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	AutomaticDoor ad;
	
	// 2. If the enum State will be altered within the AutomaticDoor class, then the AD class clients will hav to be altered.
	if (AutomaticDoor::State::open == ad.GetState())
	{
		cout << "main - the door is open" << endl;
	}
	
	// 3.
	AutomaticDoorWithGoodInformationHiding ad1;
	if (true == ad.IsOpen())
	{
		cout << "main - the door is open" << endl;
	}

	cout << "main - end" << endl;
	return 0;
}

