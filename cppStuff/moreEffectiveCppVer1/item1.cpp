#include <iostream>

using namespace std;

void item1Usage()
{
	string str1("first string");
	string str2("second string");
	cout << "item1Usage - address of str1:" << &str1 << " its content:" << str1 << endl;
	cout << "item1Usage - address of str2:" << &str2 << " its content:" << str2 << endl;
	
	string& ref1 = str1;
	string* ptr1 = &str1;

	cout << "item1Usge - ptr1:" << *ptr1 << " and it points to address" << ptr1 << endl;
	ptr1 = &str2;
	cout << "item1Usge - after re-assgin ptr1 = &str2,  *ptr1 is:" << *ptr1 << " and it points to address" << ptr1 << endl;
	
	ref1 = str2;
	cout << "item1Usge - after re-assgin ref1 = str2, str1 is:" << str1 << " it address is still:" << &str1 << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	item1Usage();
	cout << "\n \n main - end" << endl;
	return 0;
}
