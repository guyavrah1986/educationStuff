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
