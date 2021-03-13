/*
360. Sort Transformed Array


Given a sorted array of integers nums and integer values a, b and c. 
Apply a quadratic function of the form f(x) = ax2 + bx + c to each element x in the array.

The returned array must be in sorted order.

Expected time complexity: O(n)

Example 1:

Input: nums = [-4,-2,2,4], a = 1, b = 3, c = 5
Output: [3,9,15,33]
Example 2:

Input: nums = [-4,-2,2,4], a = -1, b = 3, c = 5
Output: [-23,-5,1,7]
*/
#include <vector>


using std::vector;



class SortTransformedArray {

    /*
            360.Sort-Transformed-Array
        注意a等于零和正负情况，会影响结果。如果a==0时，函数结果本身就是单调的，但要根据b是否大于0来改变顺序。

        当a不等于零时，设置左右两个指针，可以根据nums[left]、num[right]离中轴线(-b/2a)的距离来移动较远的那个指针，特别注意细节，不是比较left/right和中轴线的距离。令两个指针不断靠近，直至left==right.

        也可以直接用比较两个指针对应的func[i]的大小来移动指针。当a>0时，优先移动二者之间较大的，最后结果反序；当a<0时，优先移动二者之间较小的。
    */
    vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c) 
    {
        vector<int>result;
        
        if (a==0)
        {
            for (int i=0; i<nums.size(); i++)
                result.push_back(b*nums[i]+c);
            if (b<0)
                reverse(result.begin(),result.end());
        }
        else 
        {
            int flag = (a>0);
            float mid=-b/2.0/a;
            
            int left=0;
            int right=nums.size()-1;
            while (left<=right)
            {
                if (abs(mid-nums[left])>abs(mid-nums[right]))
                {
                    result.push_back(a*nums[left]*nums[left]+b*nums[left]+c);
                    left++;
                }
                else
                {
                    result.push_back(a*nums[right]*nums[right]+b*nums[right]+c);
                    right--;
                }                
            }            
            if (flag==1) reverse(result.begin(),result.end());            
        }        
        return result;        
    }

public:
    
    vector<int> doit_twopointer(vector<int>& nums, int a, int b, int c) {
        
        int n = nums.size();
        vector<int> buf(n);
        
        for (int i = 0; i < nums.size(); i++) {
            buf[i] = a * nums[i] * nums[i] + b * nums[i] + c;
        }
            
        
        int left = 0, right = n-1;
        
        vector<int> res(n);
        
        if (a > 0)
            for (int i = n-1; i >= 0; i--) {
                if (buf[left] < buf[right]) {
                    res[i] = buf[right--];
                } else {
                    res[i] = buf[left++];
                }
            }
        else
            for (int i = 0; i < n; i++) {
                if (buf[left] < buf[right])
                    res[i] = buf[left++];
                else
                    res[i] = buf[right--];
            }
        
        return res;
    }
};