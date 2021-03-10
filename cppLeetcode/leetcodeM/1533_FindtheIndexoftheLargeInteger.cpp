/*
1533. Find the Index of the Large Integer

We have an integer array arr, where all the integers in arr are equal except for one integer which is larger than the rest of the integers. You will not be given direct access to the array, instead, you will have an API ArrayReader which have the following functions:

. int compareSub(int l, int r, int x, int y): where 0 <= l, r, x, y < ArrayReader.length(), l <= r and x <= y. The function compares the sum of sub-array arr[l..r] with the sum of the sub-array arr[x..y] and returns:
        . 1 if arr[l]+arr[l+1]+...+arr[r] > arr[x]+arr[x+1]+...+arr[y].
        . 0 if arr[l]+arr[l+1]+...+arr[r] == arr[x]+arr[x+1]+...+arr[y].
        . -1 if arr[l]+arr[l+1]+...+arr[r] < arr[x]+arr[x+1]+...+arr[y].
. int length(): Returns the size of the array.
You are allowed to call compareSub() 20 times at most. You can assume both functions work in O(1) time.

Return the index of the array arr which has the largest integer.

Follow-up:

What if there are two numbers in arr that are bigger than all other numbers?
What if there is one number that is bigger than other numbers and one number that is smaller than other numbers?
 

Example 1:

Input: arr = [7,7,7,7,10,7,7,7]
Output: 4
Explanation: The following calls to the API
reader.compareSub(0, 0, 1, 1) // returns 0 this is a query comparing the sub-array (0, 0) with the sub array (1, 1), (i.e. compares arr[0] with arr[1]).
Thus we know that arr[0] and arr[1] doesn't contain the largest element.
reader.compareSub(2, 2, 3, 3) // returns 0, we can exclude arr[2] and arr[3].
reader.compareSub(4, 4, 5, 5) // returns 1, thus for sure arr[4] is the largest element in the array.
Notice that we made only 3 calls, so the answer is valid.
Example 2:

Input: nums = [6,6,12]
Output: 2
 

Constraints:

2 <= arr.length <= 5 * 10^5
1 <= arr[i] <= 100
All elements of arr are equal except for one element which is larger than all other elements.
*/



/**
 * // This is the ArrayReader's API interface.
 * // You should not implement it, or speculate about its implementation
 * class ArrayReader {
 *   public:
 *     // Compares the sum of arr[l..r] with the sum of arr[x..y] 
 *     // return 1 if sum(arr[l..r]) > sum(arr[x..y])
 *     // return 0 if sum(arr[l..r]) == sum(arr[x..y])
 *     // return -1 if sum(arr[l..r]) < sum(arr[x..y])
 *     int compareSub(int l, int r, int x, int y);
 *
 *     // Returns the length of the array
 *     int length();
 * };
 */

class IndexOfLargeInteger {


    class ArrayReader {
    public:
      // Compares the sum of arr[l..r] with the sum of arr[x..y] 
      // return 1 if sum(arr[l..r]) > sum(arr[x..y])
      // return 0 if sum(arr[l..r]) == sum(arr[x..y])
      // return -1 if sum(arr[l..r]) < sum(arr[x..y])
      int compareSub(int l, int r, int x, int y) { return 1; };
 
      // Returns the length of the array
      int length() {return 1;};
    };

    /*
        1533.Find-the-Index-of-the-Large-Integer
        本题本质是三分搜索。我们将一个区间分为三分ABC，其中A和B的区间大小相等。如果A、B区间和相等，那么异类就在区间C里面。如果A、B区间和不相等，那么异类就在A、B较大的区间里面。

        注意外层循环的条件变成了while (right-left+1 >= 3)。原因是区间大学小于3的时候无法成功三分区间。
    */
    int doit_(ArrayReader &reader) 
    {
        int n = reader.length();
        
        int left = 0, right = n-1;        
        while (right-left+1>=3)
        {
            int k = (right-left+1)/3;
            int ret = reader.compareSub(left, left+k-1, left+k, left+2*k-1);
            if (ret==0)
            {
                left = left+2*k;                
            }
            else if (ret==1)
            {                
                right = left+k-1;
            }
            else
            {
                left = left+k;
                right = left+k*2-1;
            }
            // cout<<left<<" "<<right<<endl;
        }
        
        if (left==right) return left;
        else
        {
            if (reader.compareSub(left,left, right,right)==1)
                return left;
            else
                return right;
        }
    }


public:

    int doit_binary_search(ArrayReader &reader) {
        
        int length = reader.length();
        int left = 0, right = length-1;
        
        while (left < right) {
            
            int mid = (left + right) / 2;
            int total = right - left + 1;
            
            if (total %2 == 1) {

                int res = reader.compareSub(left, mid-1, mid+1, right);
                
                if (res == 0) return mid;
            
                if (res > 0)
                    right = mid - 1;
                else 
                    left = mid + 1;
                
            } else {
                
                int res = reader.compareSub(left, mid, mid+1, right);
                
                if (res > 0)
                    right = mid;
                else
                    left = mid+1;
            }
        }
        
        return left;
    }
};