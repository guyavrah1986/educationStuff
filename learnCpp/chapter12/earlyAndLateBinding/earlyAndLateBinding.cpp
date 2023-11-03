#include <iostream>

using namespace std;

static void print_object(const char *name, void *this_, size_t size)
{
	void** tmp = reinterpret_cast<void**>(this_);
	size_t i;
	printf("created %s at address %p of size %zu\n", name, this_, size);
	for(i = 0 ; i < size / sizeof(void*) ; ++i)
	{
		printf("  pointer[%zu] == %p\n", i, tmp[i]);
	}
}

int add(int a, int b)
{
    return a + b;
}

int sub(int a, int b)
{
    return a - b;
}

int mul(int a, int b)
{
    return a * b;
}

int divide(int a, int b)
{
    return a / b;
}


int main(int argc, char** argv)
{
	cout << "main - start" << endl;
    int input;
    cout << "main - please enter your choice" << endl;
    cin >> input;
    int (*funcPointer)(int, int); 
    int a = 6, b = 2;
    switch(input)
    {
        case 1: funcPointer = &add;
                break;
        case 2: funcPointer = &sub;
                break;
        case 3: funcPointer = &mul;
                break;
        case 4: funcPointer = &divide;
                break;
    }
    
    cout << "main - running the desired function" << endl;
    int res = (*funcPointer)(a, b);
    cout << "main - result of the desired function is:" << res << endl;
	cout << "main - end" << endl;
	return 0;
}
