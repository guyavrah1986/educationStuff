// ===========================================================================================================================================================
// ===========================================================================================================================================================
/*
* Suppose we have the following code:
*	
*class Foo 
*{
*	
*	public:	
*	func1(.....); // If A is called, a new thread will be created and the corresponding function will be executed.			
*	func2(.....); // same as above 
*	func3(.....); // same as above 	
*}
*	
*Foo f;
*	
*f.func1(.....);	
*f.func2(.....);	
*f.func3(.....);
* 
*
* i) 	Can you design a mechanism to make sure that func2 is executed after func1, and func3 is ex-ecuted after func2?
*/
// ===========================================================================================================================================================
// ===========================================================================================================================================================

// answer to question i)

#include <iostream>
#include <thread>
#include <vector>
#include <atomic> 
#include <unistd.h>

using namespace std;

void g_task(const string str)
{
	cout << "g_task - " << str << " " << endl;
}

class Q1
{
	public:
		Q1() : m_counter(0)
		{
			cout << "Q1::Q1" << endl;
		}

		void func1() 
		{ 
			cout << "Q1::A - start" << endl;
			//if (m_counter == 0)
			{
				cout << "Q1::A - within if" << endl;
				thread t1(g_task, "starting thread of A");
				t1.join();
				m_counter++;
			}
			cout << "Q1::A - end" << endl;
		}

		void func2() 
		{ 
			cout << "Q1::B - start" << endl;
			/*			
			while (m_counter != 1)
			{
				cout << "Q1::B - waiting..." << endl;
			}
			*/
			{
				cout << "Q1::B - within if" << endl;
				thread t1(g_task, "starting thread of B");
				t1.join();
				m_counter++;
			}
			cout << "Q1::B - end" << endl;
		}

		void func3() 
		{ 
			cout << "Q1::C - start" << endl;
			/*			
			while (m_counter != 2)
			{
				cout << "Q1::C - waiting..." << endl;
			}
			*/

			{
				cout << "Q1::C - within if" << endl;
				thread t1(g_task, "starting thread of C");
				t1.join();
				m_counter++;
			}
			cout << "Q1::C - end" << endl;
		}

	private:
		atomic<int> m_counter;
};





int main(int argc, char** argv)
{
	cout << "main - start \n \n" << endl;

	Q1 q1;
	q1.func1();
	q1.func2();
	q1.func3();


	sleep(1);
	cout << "\n \n main - end" << endl;
	return 0;
}
