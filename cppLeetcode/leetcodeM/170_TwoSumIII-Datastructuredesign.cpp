/*
170. Two Sum III - Data structure design


Design a data structure that accepts a stream of integers and checks if it has a pair of integers that sum up to a particular value.

Implement the TwoSum class:

    .TwoSum() Initializes the TwoSum object, with an empty array initially.
    .void add(int number) Adds number to the data structure.
    .boolean find(int value) Returns true if there exists any pair of numbers whose sum is equal to value, otherwise, it returns false.
 

Example 1:

Input
["TwoSum", "add", "add", "add", "find", "find"]
[[], [1], [3], [5], [4], [7]]
Output
[null, null, null, null, true, false]

Explanation
TwoSum twoSum = new TwoSum();
twoSum.add(1);   // [] --> [1]
twoSum.add(3);   // [1] --> [1,3]
twoSum.add(5);   // [1,3] --> [1,3,5]
twoSum.find(4);  // 1 + 3 = 4, return true
twoSum.find(7);  // No two integers sum up to 7, return false
 

Constraints:

-105 <= number <= 105
-231 <= value <= 231 - 1
At most 5 * 104 calls will be made to add and find.

170.Two-Sum-III-Data-structure-design
不要试图构建一个存放所有两两之和的Set，那样会超时。

正确的思想应该是构建元素及其出现次数的映射 unordered_map<int,vector>Map，因为这样的Map本身兼具Set的元素不相容的功能.

当find(val)时，遍历所有Map里的元素x，查找val-x是否也在Map里。同时需要考虑x=val-x的情况。

*/
#include <unordered_map>

using std::unordered_map;


class TwoSum {
    
    unordered_map<int,int>Map;

public:

    // Add the number to an internal data structure.
	void add(int number) 
	{
	    Map[number]++;   
	}

    // Find if there exists any pair of numbers which sum is equal to the value.
	bool find(int value) 
	{
	    for (auto a:Map)
	    {
	        if (value-a.first!=a.first)
	        {
	           if (Map.find(value-a.first)!=Map.end())
	                return true;;
	        }
	        else if (value-a.first==a.first)
	        {
	            if (a.second>1)
	                return true;
	        }
	    }
	    
	    return false;
	}
};