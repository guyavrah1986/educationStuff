// ==================================================================================================================================================
// 
//
// ==================================================================================================================================================
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <iostream>
#include <string>

#include "simpleObj.h"
#include "catch.hpp"

using namespace std;


unsigned int Factorial(unsigned int number)
{
	return number <= 1 ? number : Factorial(number - 1)*number;
}

TEST_CASE("Factorials are computed", "[factorial]") 
{
	REQUIRE(Factorial(1) == 1);
	REQUIRE(Factorial(2) == 2);
	REQUIRE(Factorial(3) == 6);
	REQUIRE(Factorial(10) == 3628800);
}

/*
int main(int argc, char* argv[]) 
{
	cout << "main - start" << endl;

	char c;
	cout << "main - enter any key terminate and hit ENTER" << endl;
	cin >> c;
	return 0;
}
*/