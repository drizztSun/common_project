/*
275. H-Index II


Given an array of citations sorted in ascending order (each citation is a non-negative integer) of a researcher, write a function to compute the researcher's h-index.

According to the definition of h-index on Wikipedia: "A scientist has index h if h of his/her N papers have at least h citations each, and the other N − h papers have no more than h citations each."

Example:

Input: citations = [0,1,3,5,6]
Output: 3 
Explanation: [0,1,3,5,6] means the researcher has 5 papers in total and each of them had 
             received 0, 1, 3, 5, 6 citations respectively. 
             Since the researcher has 3 papers with at least 3 citations each and the remaining 
             two with no more than 3 citations each, her h-index is 3.
Note:

If there are several possible values for h, the maximum one is taken as the h-index.

Follow up:

This is a follow up problem to H-Index, where citations is now guaranteed to be sorted in ascending order.
Could you solve it in logarithmic time complexity?
*/

#include <vector>


using std::vector;


class HIndexII {

    /*
        275.H-Index-II
        解法1：
        此题有很多做法，参见 274 H-Index. 但用时最快的应该是二分搜索的方法。

        设文章总数N=citations.size()

        将citations数组排序后，按位置进行常规的二分搜索。如果发现 citations[mid]==N-mid(从右往左累加的文章总数)，则可以证明 H-index 就是 citations[mid]，因为继续左移的话citation必定会减少，右移的话则文章总数（从右往左计算引用数大于citations[mid]的）会减少，故不可能有其他的解。  

        如果最后收敛到left==right都没有退出，请仔细考虑会是什么情况？结合二分的判断条件，答案是：此时的元素i是使得(N-i)与citations[i]最接近的。故此时查看citations[i]（引用数） 和 Citations.size()-i（文章数）哪个更小，即为H-index.

        解法2：
        最简洁的方法是：

        从后面往前找，每找到一篇，说明有N-i篇论文，其最小的引用数是citations[i]。如果N-i<=citations[i]，说明我们仍然可以有机会增多文章数目（代表了H index），代价是再往前走减小文章引用数。找到满足条件的最小的i，得到最大的N-i，这样答案就是 H = N-i;
    
    */
    int doit_binary_search(vector<int>& citations) 
    {
        int left=0;
        int N=citations.size();
        int right=N-1;
        int mid;
        
        if (N==0) return 0;
        
        while (left<right)
        {
            int mid= left+(right-left)/2;
            
            if (N-mid==citations[mid])
                return citations[mid];
            else if (N-mid<citations[mid])
                right = mid;
            else
                left= mid+1;
        }
        
        return std::min(N-left,citations[left]);
    }

    int hIndex(vector<int>& citations) 
    {            
        int N = citations.size();
        int i = N-1;
        while (i>=0 && N-i<=citations[i])
            i--;
        return N-(i+1);
    }


public:

    int doit_binary_search(vector<int>& citations) {

        int n = citations.size();
        int left = 0, right = citations.size();
        
        while (left < right) {
            
            int mid = (left + right) / 2;
            
            if (citations[mid] >= n - mid)
                right = mid;
            else
                left = mid +  1;
        }
        
        return n - left;
    }
};