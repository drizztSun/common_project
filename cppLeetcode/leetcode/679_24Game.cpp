/*

# 679. 24 Game

# You have 4 cards each containing a number from 1 to 9.
# You need to judge whether they could operated through *, /, +, -, (, ) to get the value of 24.

# Example 1:
# Input: [4, 1, 8, 7]
# Output: True
# Explanation: (8-4) * (7-1) = 24

# Example 2:
# Input: [1, 2, 1, 2]
# Output: False

# Note:
# The division operator / represents real division, not integer division. For example, 4 / (1 - 2/3) = 12.
# Every operation done is between two numbers. In particular, we cannot use - as a unary operator.
# For example, with [1, 1, 1, 1] as input, the expression -1 - 1 - 1 - 1 is not allowed.
# You cannot concatenate numbers together. For example, if the input is [1, 2, 1, 2], we cannot write this as 12 + 12.


*/

#include <cmath>
#include <vector>
#include <algorithm>
#include <functional>

using std::vector;


class JudgePoint24 {

	/*
		679.24-Game
		回想一下平时24点是怎么玩的。不管最终的策略是什么，都是要先选两张牌做运算，算出一个数值，然后和剩下的两张牌一起考虑。于是接下来就等于三张牌算24点。OK，递归的思路就这么出来了。所以，那些乘除法、括号的优先结合法则，都是障眼法，其实都不需要考虑。

		总结一下：手头有N张牌的时候(K<=4)，要随机选出两张（有序），剩下的就不用管顺序了。这样的排列组成了一个排列的集合vector<vector<double>>permuations。对于其中的每一种排列，我们对于那两张有序的牌分别做加减乘除的运算，
		将得到的结果再放回剩下的N-2张牌里面,相当于变成N-1张牌.于是我们发现这是一个递归任务,我们下一步就是在N-1牌里算24点，同样需要先随机挑两张,重复上面的步骤。手头的牌只有一张了，那查看它是否为24即可。

		需要注意，所有的牌必须处理成浮点，因为涉及到除法。
	*/

public:


    bool judgePoint24(vector<int>& nums) 
    {
        vector<double>Nums;
        for (auto x:nums) Nums.push_back(x*1.0);
        return DFS(Nums);
    }
    
    bool DFS(vector<double>& nums)
    {
        int m = nums.size();
        if (m==1) return (abs(nums[0]-24.0)<1e-6);
            
        for (int i=0; i<m; i++)
            for (int j=0; j<m; j++)
            {
                if (i==j) continue;
                
                vector<double>newNums;
                for (int k=0; k<m; k++)
                    if (k!=i && k!=j) newNums.push_back(nums[k]);

                newNums.push_back(-1);
                
                double a = nums[i];
                double b = nums[j];
                
                newNums.back() = a+b;
                if (DFS(newNums)) return true;
            
                newNums.back() = a-b;
                if (DFS(newNums)) return true;
            
                newNums.back() = a*b;
                if (DFS(newNums)) return true;
            
                if (b!=0.0)
                {
                    newNums.back() = a/b;
                    if (DFS(newNums)) return true;
                }            
            }        
        
            return false;
    }

public:

	vector<vector<vector<int>>>AllPermuations;

    bool judgePoint24(vector<int>& nums) 
    {
        vector<double>Nums;
        for (auto x:nums) Nums.push_back(x*1.0);
        
        AllPermuations.resize(5);
        AllPermuations[4] = CalPermutation(4);
        AllPermuations[3] = CalPermutation(3);
        AllPermuations[2] = CalPermutation(2);
        
        return DFS(Nums);
    }
    
    bool DFS(vector<double>& nums)
    {
        int k = nums.size();
        if (k==1) return (abs(nums[0]-24.0)<1e-6);
            
        vector<vector<int>>permutations = AllPermuations[k];
        
        for (int i=0; i<permutations.size(); i++)
        {
            vector<double>newNums(k-1);
            for (int j=0; j<k-2; j++)
                newNums[j] = nums[permutations[i][j]];
            
            double a = nums[permutations[i][k-2]];
            double b = nums[permutations[i][k-1]];
            
            newNums.back() = a+b;
            if (DFS(newNums)) return true;
            
            newNums.back() = a-b;
            if (DFS(newNums)) return true;
            
            newNums.back() = a*b;
            if (DFS(newNums)) return true;
            
            if (b!=0.0)
            {
                newNums.back() = a/b;
                if (DFS(newNums)) return true;
            }            
        }
        
        return false;
    }
    
    vector<vector<int>>CalPermutation(int k)
    {
        vector<vector<int>>results;
        vector<int>nums;
        for (int i=0; i<k; i++) nums.push_back(i);
        do
        {
            results.push_back(nums);
        }while (next_permutation(nums.begin(),nums.end()));
        
        return results;        
    }


public:

    bool judgePoint24(vector<int>& arr) {
        
        vector<double> Nums;
        for (auto c: arr)
            Nums.push_back(c * 1.0);
        
        std::function<bool(vector<double>&)> dfs = [&](vector<double>& nums) {
            
            int m = nums.size();
            if (m == 1) return abs(nums[0] - 24.0) < 1e-6;
            
            for (int i = 0; i < m; i++) {
                
                for (int j = 0; j < m; j++) {
                    
                    if (i == j) continue;
                    
                    vector<double> newobj;
                    
                    for (int k = 0; k < m; k++)
                        if (i != k && j != k) newobj.push_back(nums[k]);
                    
                    newobj.push_back(-1);
                    
                    double a = nums[i], b = nums[j];
                    
                    newobj.back() = a + b;
                    if (dfs(newobj)) return true;
                    
                    newobj.back() = a - b;
                    if (dfs(newobj)) return true;
                    
                    newobj.back() = a * b;
                    if (dfs(newobj)) return true;
                    
                    if (b == 0.0) continue;
                    
                    newobj.back() = a / b;
                    if (dfs(newobj)) return true;
                }
            }
            
            return false;
        };
        
        return dfs(Nums);
    }
};