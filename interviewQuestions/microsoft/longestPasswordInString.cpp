/*
 Based on the codility question:
You would like to set a password for a bank account. However, there are three restrictions on the format of the password:

it has to contain only alphanumerical characters (a?z, A?Z, 0?9);
there should be an even number of letters;
there should be an odd number of digits.
You are given a string S consisting of N characters. String S can be divided into words by splitting it at, and removing, the spaces. The goal is to choose the longest word that is a valid password. You can assume that if there are K spaces in string S then there are exactly K + 1 words.

For example, given "test 5 a0A pass007 ?xy1", there are five words and three of them are valid passwords: "5", "a0A" and "pass007". Thus the longest password is "pass007" and its length is 7. Note that neither "test" nor "?xy1" is a valid password, because "?" is not an alphanumerical character and "test" contains an even number of digits (zero).

Write a function:

int solution(string &S);

that, given a non-empty string S consisting of N characters, returns the length of the longest word from the string that is a valid password. If there is no such word, your function should return ?1.

For example, given S = "test 5 a0A pass007 ?xy1", your function should return 7, as explained above.

Assume that:

N is an integer within the range [1..200];
string S consists only of printable ASCII characters and spaces.
In your solution, focus on correctness. The performance of your solution will not be the focus of the assessment.
*/
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

int solution(string &S) 
{
    string buf;                 
    stringstream ss(S);       
    int lenOfLongestWord = -1;
    while (ss >> buf)
    {
        int currWordLen = buf.length();
        //cout << "found word:" << buf << ", with lenght of:" << currWordLen << endl;
        size_t numOfLetters = 0;
        size_t numOfDigits = 0;
        bool isAlpha = false;
        bool isDigit = false;
        bool skipWord = false;
        for (size_t i = 0; i < currWordLen; ++i)
        {
            if (isalpha(buf[i]))
            {
                ++numOfLetters;
                isAlpha = true;
            }

            if (isdigit(buf[i]))
            {
                ++numOfDigits;
                isDigit = true;
            }

            if (isAlpha == false && isDigit == false)
            {
                skipWord = true;
                break;
            }

            isAlpha = false;
            isDigit = false;
        }

        //cout << "word:" << buf << " has " << numOfLetters << " letters and " << numOfDigits << " digits" << endl; 
        if (numOfLetters  % 2 != 0)
        {
            //cout << "word:" << buf << " does NOT have an EVEN number of letters, skipping it" << endl;
            continue;
        }

        if (numOfDigits  % 2 == 0)
        {
            //cout << "word:" << buf << " does NOT have an ODD number of digits, skipping it" << endl;
            continue;
        }
        if (skipWord)
        {
            //cout << "word:" << buf << " is not a legit word, skipping it" << endl;
            continue;
        }

        if (lenOfLongestWord < currWordLen)
        {
            lenOfLongestWord = currWordLen;
        }
    }

    return lenOfLongestWord;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	string s1 = "test 5 a0A pass007 ?xy1";
	int retVal = solution(s1);
	int expectedRetVal = 7;
	if (retVal != expectedRetVal)
	{
		cout << "main - expected return value of:" << expectedRetVal << ", but got:" << retVal << endl;
		return 1;
	}
	cout << "main - end" << endl;
	return 0;
}
