#include <iostream>
#include <mutex>

using namespace std;

class SingleTone
{

	public:
		static SingleTone* GetInstance()
		{
			if (m_instance == 0)
			{
				m_mutex.lock();
				if (m_instance == 0)
				{
					m_instance = new SingleTone();
				}
			}

			return m_instance;
		}
	
	private:
		SingleTone()
		{
			cout << "SingleTone::SingleTone" << endl;
		}



	private:
		static mutex m_mutex;
		static SingleTone* m_instance;

};

SingleTone* SingleTone::m_instance = NULL;




int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	SingleTone* firstInstance = SingleTone::GetInstance();


	
	
	cout << "\n \n main - end" << endl;
	return 0;
}
