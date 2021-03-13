/*
611. Valid Triangle Number

Given an array consists of non-negative integers, your task is to count the number of triplets chosen from the array that can make triangles if we take them as side lengths of a triangle.
Example 1:
Input: [2,2,3,4]
Output: 3
Explanation:
Valid combinations are: 
2,3,4 (using the first 2)
2,3,4 (using the second 2)
2,2,3
Note:
The length of the given array won't exceed 1000.
The integers in the given array are in the range of [0, 1000].

*/
#include <algorithm>
#include <vector>

using std::vector;


class TriangleNumber {

    /*
        611.Valid-Triangle-Number
        最佳的解法是用双指针。

        将nums排序后，固定最大的位置k，则前两个元素的位置i,j需要满足其nums[i]+nums[j]>nums[k]，等效于一道“2sum larger”的题目，于是双指针的移动规则就非常清楚了。
    */
    int triangleNumber(vector<int>& nums) 
    {
        sort(nums.begin(),nums.end());
        int count=0;

        for (int k=nums.size()-1; k>=0; k--)
        {
            int i=0;
            int j=k-1;
            while (i<j)
            {
                if (nums[i]+nums[j]>nums[k])
                {
                    count+=j-i;
                    j--;
                }
                else
                    i++;
            }                   
        }
        return count;
    }

public:

    /*
        Approach 3: Linear Scan
        Algorithm

        As discussed in the last approach, once we sort the given numsnums array, we need to find the right limit of the index kk for a pair of indices (i, j)(i,j) chosen to find the countcount of elements satisfying nums[i] + nums[j] > nums[k]nums[i]+nums[j]>nums[k] for the triplet (nums[i], nums[j], nums[k])(nums[i],nums[j],nums[k]) to form a valid triangle.

        We can find this right limit by simply traversing the index kk's values starting from the index k=j+1k=j+1 for a pair (i, j)(i,j) chosen and stopping at the first value of kk not satisfying the above inequality. Again, the countcount of elements nums[k]nums[k] satisfying nums[i] + nums[j] > nums[k]nums[i]+nums[j]>nums[k] for the pair of indices (i, j)(i,j) chosen is given by k - j - 1k−j−1 as discussed in the last approach.

        Further, as discussed in the last approach, when we choose a higher value of index jj for a particular ii chosen, we need not start from the index j + 1j+1. Instead, we can start off directly from the value of kk where we left for the last index jj. This helps to save redundant computations.

        The following animation depicts the process:

        Current
        1 / 13

        Complexity Analysis

        Time complexity : O(n^2). Loop of k and j will be executed O(n^2) times in total, because, we do not reinitialize the value of kk for a new value of jj chosen(for the same i). Thus the complexity will be O(n^2+n^2).

        Space complexity : O(\log n)O(logn). Sorting takes O(\log n)O(logn) space.
    */
    
    int doit_sort_linear(vector<int>& nums) {
        
        std::sort(begin(nums), end(nums));
        int cnt = 0;
        
        for  (int i = 0; i < nums.size(); i++) {
            
            for (int j = i+1, k = i+2; j < nums.size() - 1 && nums[i] != 0 ; j++) {
                
                while (k < nums.size() && nums[i] + nums[j] > nums[k]) k++;
                
                cnt += k - j -1;     
            }

        }
        
        return cnt;
    }

    /*
        Approach 2: Using Binary Search
        Algorithm

        If we sort the given numsnums array once, we can solve the given problem in a better way. This is because, if we consider a triplet (a, b, c)(a,b,c) such that a ≤ b ≤ c, we need not check all the three inequalities for checking the validity of the triangle formed by them. But, only one condition a + b > ca+b>c would suffice. This happens because c ≥ b and c ≥ a. Thus, adding any number to cc will always produce a sum which is greater than either aa or bb considered alone. Thus, the inequalities c + a > bc+a>b and c + b > ac+b>a are satisfied implicitly by virtue of the property a < b < ca<b<c.

        From this, we get the idea that we can sort the given numsnums array. Then, for every pair (nums[i], nums[j])(nums[i],nums[j]) considered starting from the beginning of the array, such that j > ij>i(leading to nums[j] ≥ nums[i]), we can find out the count of elements nums[k]nums[k](k > jk>j), which satisfy the inequality nums[k] > nums[i] + nums[j]nums[k]>nums[i]+nums[j]. We can do so for every pair (i, j)(i,j) considered and get the required result.

        We can also observe that, since we've sorted the numsnums array, as we traverse towards the right for choosing the index kk(for number nums[k]nums[k]), the value of nums[k]nums[k] could increase or remain the same(doesn't decrease relative to the previous value). Thus, there will exist a right limit on the value of index kk, such that the elements satisfy nums[k] > nums[i] + nums[j]nums[k]>nums[i]+nums[j]. Any elements beyond this value of kk won't satisfy this inequality as well, which is obvious.

        Thus, if we are able to find this right limit value of kk(indicating the element just greater than nums[i] + nums[j]nums[i]+nums[j]), we can conclude that all the elements in numsnums array in the range (j+1, k-1)(j+1,k−1)(both included) satisfy the required inequality. Thus, the countcount of elements satisfying the inequality will be given by (k-1) - (j+1) + 1 = k - j - 1(k−1)−(j+1)+1=k−j−1.

        Since the numsnums array has been sorted now, we can make use of Binary Search to find this right limit of kk. The following animation shows how Binary Search can be used to find the right limit for a simple example.

        Current
        1 / 5
        Another point to be observed is that once we find a right limit index k_{(i,j)}k 
        (i,j)
        ​	
        for a particular pair (i, j)(i,j) chosen, when we choose a higher value of jj for the same value of ii, we need not start searching for the right limit k_{(i,j+1)}k 
        (i,j+1)
        ​	
        from the index j+2j+2. Instead, we can start off from the index k_{(i,j)}k 
        (i,j)
        ​	
        directly where we left off for the last jj chosen.

        This holds correct because when we choose a higher value of jj(higher or equal nums[j]nums[j] than the previous one), all the nums[k]nums[k], such that k < k_{(i,j)}k<k 
        (i,j)
        ​	
        will obviously satisfy nums[i] + nums[j] > nums[k]nums[i]+nums[j]>nums[k] for the new value of jj chosen.

        By taking advantage of this observation, we can limit the range of Binary Search for kk to shorter values for increasing values of jj considered while choosing the pairs (i, j)(i,j).


        Complexity Analysis

        Time complexity : O(n^2 * log n). In worst case inner loop will take nlogn (binary search applied nn times).

        Space complexity : O(logn). Sorting takes O(\log n)O(logn) space.

    */
    int doit_sort_binary_search(vector<int>& nums) {

        std::sort(begin(nums), end(nums));
        int cnt = 0;
        
        for (int i = 0; i < nums.size(); i++) {
            
            for (int j = i+1, k = i+2; j < nums.size() -1 && nums[i] != 0; j++) {
                
                cnt += std::lower_bound(begin(nums) + j, end(nums), nums[i] + nums[j]) - (begin(nums) + j) - 1;
                
            }
        }
        
        return cnt;
    }
};