/*
274. H-Index


Given an array of citations (each citation is a non-negative integer) of a researcher, write a function to compute the researcher's h-index.

According to the definition of h-index on Wikipedia: "A scientist has index h if h of his/her N papers have at least h citations each, and the other N − h papers have no more than h citations each."

Example:

Input: citations = [3,0,6,1,5]
Output: 3 
Explanation: [3,0,6,1,5] means the researcher has 5 papers in total and each of them had 
             received 3, 0, 6, 1, 5 citations respectively. 
             Since the researcher has 3 papers with at least 3 citations each and the remaining 
             two with no more than 3 citations each, her h-index is 3.
Note: If there are several possible values for h, the maximum one is taken as the h-index.


*/

#include <vector>
#include <algorithm>
#include <map>


using std::map;
using std::vector;


class HIndex {

    /*
        274.H-Index
        类似的题目里 275.H-Index II 给出排序后的citations，可以用双指针来做。本题中，考虑如果不先行排序的话，需要用到Hash表。

        首先遍历数组，建立映射：引用数 -> 符合该引用数的文章数目。然后把Map放进pair类型的数组中，方便用sort直接排序。

                for (int i=0; i<citations.size(); i++)
                    Map[citations[i]]++;
                auto q = vector<pair<int,int>>(Map.begin(),Map.end());
                sort(q.begin(),q.end());
        然后对于q数组，从后往前考察：

                int sum=0;        
                for (int i=q.size()-1; i>=0; i--)
                {
                    if (q[i].first>sum+q[i].second) // 文章总数还小于citation量，可以尝试进一步扩大范围（考虑引用量更少的文章）
                        sum+=q[i].second;
                    else if (q[i].first==sum+q[i].second) // 文章总数恰好等于citation量，可以证明这就是最优解
                        return q[i].first;
                    else if (q[i].first<sum+q[i].second)  // 文章总数已经大于citation量，说明q[i]不可完全列入考虑范围。
                        return max(q[i].first,sum);       // 这个操作非常关键！仔细思考。
                }
    */
    int hIndex_hashtable(vector<int>& citations) 
    {
        if (citations.size()==0) return 0;
        
        map<int,int>Map;
        for (int i=0; i<citations.size(); i++)
            Map[citations[i]]++;
        auto q = vector<std::pair<int,int>>(Map.begin(),Map.end());
        
        int sum=0;
        
        for (int i=q.size()-1; i>=0; i--)
        {
            if (q[i].first>sum+q[i].second)
                sum+=q[i].second;
            else if (q[i].first==sum+q[i].second)
                return q[i].first;
            else
                return std::max(q[i].first,sum);
        }
        
        return sum;        
    }

    int hIndex_binary_search(vector<int>& citations) 
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
        if (citations.size()==0) return 0;
        
        sort(citations.begin(),citations.end());
        
        int sum=0;
        int i=citations.size()-1;
        
        while (i>=0)
        {
            sum++;
            
            if (citations[i]==sum)
                return sum;
            else if (citations[i]>sum)
                i--;
            else
            {
                return std::max(citations[i],sum-1);
            }
        }
        
        return sum;
    }

public:

    /*
        Approach #1 (Sorting) [Accepted]
        Intuition

        Think geometrically. Imagine plotting a histogram where the yy-axis represents the number of citations for each paper. After sorting in descending order, hh-index is the length of the largest square in the histogram.

        h-index

        Figure 1. hh-index from a plot of decreasing citations for papers

        Algorithm

        To find such a square length, we first sort the citations array in descending order. After sorting, if \mathrm{citations}[i] \gt icitations[i]>i, then papers 00 to ii all have at least i + 1i+1 citations.

        Thus, to find hh-index, we search for the largest ii (let's call it i'i 
        ′
        ) such that

        \mathrm{citations}[i] \gt icitations[i]>i

        and therefore the hh-index is i' + 1i 
        ′
        +1.

        For example:

        ii	0	1	2	3	4	5	6
        sorted citations	10	9	5	3	3	2	1
        \mathrm{citations}[i] \gt icitations[i]>i?	true	true	true	false	false	false	false
        In this example, we know that the largest ii with \mathrm{citations}[i] \gt icitations[i]>i is i'=2i 
        
        through binary search after sorting. However, since comparison sorting has a time complexity of O(n \log n)O(nlogn) which dominates the performance of entire algorithm (linear search is O(n)O(n)). Using a binary search (O(\log n)O(logn)) instead of linear search won't change the asymptotic time complexity.

        Also note that, we deduced the algorithm in descending for simplicity. Usually the sort function provided by default is in ascending order. The same principles applies to both ascending order and descending order. In the case of ascending order, we just scan it from backward.


        Complexity Analysis

        Time complexity : O(n\log n)O(nlogn). Comparison sorting dominates the time complexity.

        Space complexity : O(1)O(1). Most libraries using heap sort which costs O(1)O(1) extra space in the worst case.
    */
    int doit_sort(vector<int>& citations) {
        
        std::sort(begin(citations), end(citations));
        int n = citations.size(), i = 0;
        
        while (i < n && citations[n-1-i] > i) i++;
        
        return i;
    }

    /*
        Approach #2 (Counting) [Accepted]
        Intuition

        Comparison sorting algorithm has a lower bound of O(n\log n)O(nlogn). To achieve better performance, we need non-comparison based sorting algorithms.

        Algorithm

        From Approach #1, we sort the citations to find the h-index. However, it is well known that comparison sorting algorithms such as heapsort, mergesort and quicksort have a lower bound of O(n\log n)O(nlogn). The most commonly used non-comparison sorting is counting sort.

        Counting sort operates by counting the number of objects that have each distinct key value, and using arithmetic on those tallies to determine the positions of each key value in the output sequence. Its running time is linear in the number of items and the difference between the maximum and minimum keys, so it is only suitable for direct use in situations where the variation in keys is not significantly greater than the number of items.

        ---by Wikipedia

        However, in our problem, the keys are the citations of each paper which can be much larger than the number of papers nn. It seems that we cannot use counting sort. The trick here is the following observation:

        Any citation larger than nn can be replaced by nn and the hh-index will not change after the replacement

        The reason is that hh-index is upper bounded by total number of papers nn, i.e.

        h \leq nh≤n

        In the diagram, replacing citations greater than nn with nn is equivalent to cutting off the area where y > ny>n.

        h-index cut off

        Figure 2. cutting off the area with citations more than nn

        Apparently, cutting that area off will not change the largest square and the hh-index.

        After we have the counts, we can get a sorted citations by traversing the counts array. And the rest is the same as Approach #1.

        But we can do even better. The idea is that we don't even need to get sorted citations. We can find the hh-index by using the paper counts directly.

        To explain this, let's look at the following example:

        \mathrm{citations} = [1, 3, 2, 3, 100]citations=[1,3,2,3,100]

        The counting results are:

        kk	0	1	2	3	4	5
        count	0	1	1	2	0	1
        s_ks 
        k
        ​	
            5	5	4	3	1	1
        The value s_ks 
        k
        ​	
        is defined as "the sum of all counts with citation \geq k≥k" or "the number of papers having, at least, kk citations". By definition of the h-index, the largest kk with k \leq s_kk≤s 
        k
        ​	
        is our answer.

        After replacing 100100 with n = 5n=5, we have \mathrm{citations} = [1, 3, 2, 3, 5]citations=[1,3,2,3,5]. Now, we count the number of papers for each citation number 00 to 55. The counts are [0, 1, 1, 2, 0, 1][0,1,1,2,0,1]. The first kk from right to left (55 down to 00) that have k \leq sk≤s is the hh-index 33.

        Since we can calculate s_ks 
        k
        ​	
        on the fly when traverse the count array, we only need one pass through the count array which only costs O(n)O(n) time.


        Complexity Analysis

        Time complexity : O(n)O(n). There are two steps. The counting part is O(n)O(n) since we traverse the citations array once and only once. The second part of finding the hh-index is also O(n)O(n) since we traverse the papers array at most once. Thus, the entire algorithm is O(n)O(n)

        Space complexity : O(n)O(n). We use O(n)O(n) auxiliary space to store the counts.

    */
    int hIndex(vector<int>& citations) {
        
        int n = citations.size();
        vector<int> cnt(n+1);
        
        for (auto c : citations) cnt[std::min(c, n)]++;
        
        int k = n;
        for (int s = cnt[n]; k > s; s += cnt[k]) k--;
        
        return k;
    }
};
