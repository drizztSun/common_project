/*
440. K-th Smallest in Lexicographical Order

Given integers n and k, find the lexicographically k-th smallest integer in the range from 1 to n.

Note: 1 ≤ k ≤ n ≤ 10^9.

Example:

Input:
n: 13   k: 2

Output:
10

Explanation:
The lexicographical order is [1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9], so the second smallest number is 10.

*/



class KthNumber {

    /*
        440.K-th-Smallest-in-Lexicographical-Order
        本题初看和386.Lexicographical-Numbers非常相似，但解法大不相同．在３８６题中，因为需要将按照字典序从小到大所有的元素打印出来，所以可以用构造法把这些数都找出来．但本题中，如果Ｋ很大，要将从１到Ｋ个的字典序元素都生成是很费时的．

        此题的解法很巧妙．举个例子，假设n=23456,k=10000，我们期待的结果是Ｒ．我们如何找到Ｒ呢？我们肯定会先尝试Ｒ的第一个数字是否会是１．此时，一个快速的筛选准则是：考察所有小于ｎ的１ｘｘｘｘ（ｘ的个数随意），
        可以计算总共有几个这样的数，我们假设是Ｍ．我们应该发现，这Ｍ个数其实就是字典序里的前Ｍ个（因为首元素是１，字典序最小）．如果Ｍ<k的话，那么我们就不用考虑所有的1xxxx，只需要从２xxxx开始寻找第k-M个字典序的数．
        
        如果M>k的话，我们就确定了首元素必须是１，进而考虑第二个数字，也是从１的可能性考虑起－－我们发现，这就是在递归重复之前的步骤．

        代码的流程大致如下：

        int FindKthNumberBeginWith(prefix,k)
        {
            if (k==0) return prefix;
            
            for i=0 to 9
            {
                count = TotalNumbersBeginWith(prefix+[i]);
                if (count<k)
                    k -= count;
                else 
                    return FindKthNumberBeginWith(prefix+[i],k-1)
            }
        }
    */
     int findKthNumber(int n, int k) 
    {        
        return FindKthNumberBeginWith(0,n,k);
    }
    
    // return the Lexicographically Kth element that begin with the prefix
    // excluding the prefix itself
    int FindKthNumberBeginWith(int prefix, int n, int k)
    {       
        if (k==0) return prefix;        
        
        for (int i=(prefix==0?1:0); i<=9; i++)
        {
            int count = TotalNumbersBeginWith(prefix*10+i,n);
            if (count<k)
                k-=count;
            else
                return FindKthNumberBeginWith(prefix*10+i,n,k-1);
        }
    }
    
    // return how many numbers that begin with the prefix and within the range of n 
    // including the prefix itself
    int TotalNumbersBeginWith(long long prefix, int n)
    {
        long long fac = 1;
        int count = 0;
        
        for(int digit = 1; digit <= 9; digit++) 
        {
            long long min = prefix*fac;
            long long max = prefix*fac+fac-1;
            if(n < min)
                break;
            else if(min <= n && n <= max) 
            {
                count += (n-min+1);
                break;
            }
            else  
                count += fac;
            fac *= 10;
        }
        return count;
    }
};