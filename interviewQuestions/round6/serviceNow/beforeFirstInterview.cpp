/*
You are given an integer array nums. You are initially positioned at the array's first index, and each element in the array represents your maximum jump length at that position.

Return true if you can reach the last index, or false otherwise.

 

Example 1:

Input: nums = [2,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
Example 2:

Input: nums = [3,2,1,0,4]
Output: false
Explanation: You will always arrive at index 3 no matter what. Its maximum jump length is 0, which makes it impossible to reach the last index.
*/
#include <iostream>

using namespace std;
class Solution
{

private:
    bool isLastIndex(const size_t index)
    {
        if (index == m_len - 1)
        {
            return true;
        }

        return false;
    }

    bool attemptAllJumpsFromGivenIndex(const size_t index, const vector<int>& nums)
    {
        // stop condition#1 - reached the end of the array
        if (true == isLastIndex(index))
        {
            return true;
        }

        // do the recursive call
        size_t numOfMaxJumps = nums[index];
        cout << "Solution::attemptAllJumpsFromGivenIndex - maximum nuber of jumps possible from index:" << index << ", is:" << numOfMaxJumps << endl;
        for (size_t numJumpsToPerform = 1; numJumpsToPerform <= numOfMaxJumps; ++numJumpsToPerform)
        {
            if (true == attemptAllJumpsFromGivenIndex(index + numJumpsToPerform, nums)) //isLastIndex(index + num[index + numJumpsToPerform])
            {
                return true;
            }
        }

        return false;
    }

    size_t m_len;

public:
    bool canJump(vector<int>& nums)
    {
        this->m_len = nums.size();
        cout << "Solution::canJump - vector size is:" << m_len << endl;
        return attemptAllJumpsFromGivenIndex(0, nums);
    }
};


//==============================================================================================================================================================
//==============================================================================================================================================================

/*
Given an input string s, reverse the order of the words.

A word is defined as a sequence of non-space characters. The words in s will be separated by at least one space.

Return a string of the words in reverse order concatenated by a single space.

Note that s may contain leading or trailing spaces or multiple spaces between two words. The returned string should only have a single space separating the words. Do not include any extra spaces.

 

Example 1:

Input: s = "the sky is blue"
Output: "blue is sky the"
Example 2:

Input: s = "  hello world  "
Output: "world hello"
Explanation: Your reversed string should not contain leading or trailing spaces.
Example 3:

Input: s = "a good   example"
Output: "example good a"
Explanation: You need to reduce multiple spaces between two words to a single space in the reversed string.
 */
class Solution 
{
private:
    short moveToNextNonWhiteSpaceChar(string s, short currIndex)
    {
        while (currIndex >= 0 && ' ' == s[currIndex])
        {
            --currIndex;
        }

        return currIndex;
    }

public:
    string reverseWords(string s)
    {
        cout << "got sentance with total length of:" << s.length() << " characters" << endl;
        string retStr = "";
        char endCurrWord;
        short currIndex = s.length() - 1;
        while (currIndex >= 0)
        {
            // pass all whitespace, when you are done, this marks the 
            // end of the current word
            currIndex = moveToNextNonWhiteSpaceChar(s, currIndex);
            if (currIndex < 0)
            {
                break;
            }
            
            short endOfCurrWord = currIndex;

            // move on as long as the current char is not " "
            while (currIndex >= 0 && ' ' != s[currIndex])
            {
                --currIndex;
            }

            // compose/extract the word: it begins in currIndex + 1 and ends
            // at endOfCurrWord
            retStr += s.substr(currIndex + 1, endOfCurrWord - currIndex) + " ";
        }

        // remove the extra white space from the last word - it is fine, cause
        // it is guaranteed that there will be at least one word
        retStr.pop_back();
        return retStr;    
    }
};
