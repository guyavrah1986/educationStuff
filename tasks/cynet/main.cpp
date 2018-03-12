#include <iostream>
#include <cwctype>	// for iswprint
#include <codecvt>
#include <string>
#include <vector>
#include <locale>

using namespace std;

enum EnIsPrintableAscii
{
	IS_PRINTABLE_NULL = 0,
	IS_PRINTABLE_VALID_CHAR,
	IS_PRINTABLE_NOT_VALID_CHAR
};

wstring wstring_convert_from_char(const char *str)
{
    wstring_convert<codecvt_utf8<wchar_t>, wchar_t> converter;
    return converter.from_bytes( str );
}

wstring wstring_convert_from_bytes(const vector<char>& v)
{
    wstring_convert<codecvt_utf8<wchar_t>, wchar_t> converter;
    return converter.from_bytes( v.data(), v.data() + v.size() );
}



enum EnIsPrintableAscii isUnicodePrintableCharacter(wchar_t c)
{
	if (iswprint(static_cast<wint_t>(c)) == 0)
	{
		// now, check if it is NULL terminator
		if (c == 0)
		{
			return IS_PRINTABLE_NULL;
		}
		
		return IS_PRINTABLE_NOT_VALID_CHAR;
	}
	else
	{
		return IS_PRINTABLE_VALID_CHAR;
	}
}


// ----- unit tests ------
void foo()
{
	vector<char> vec { 'a', 'b', 'c', 'd', 'e' };
	wstring str1 = wstring_convert_from_bytes(vec);
	wstring str2 = L"abcde";

	cout << "foo - size of vec is:" << vec.size() << endl;
	cout << "foo - length of str1 (wstring):" << str1.length() << endl;
	cout << "foo - length of str2 (wstring):" << str2.length() << endl;
}


bool invokeUnitTestsIsAsciiDetector()
{
	cout << "invokeUnitTestsIsAsciiDetector - start" << endl;
	return false;
}

// ----- unit tests ------

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	foo();
	
	cout << "\n \n main - end" << endl;
	return 0;
}
