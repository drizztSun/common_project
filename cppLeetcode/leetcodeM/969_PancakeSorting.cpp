/*
 
 969. Pancake Sorting
 
 
 Given an array A, we can perform a pancake flip: We choose some positive integer k <= A.length, then reverse the order of the first k elements of A.
 We want to perform zero or more pancake flips (doing them one after another in succession) to sort the array A.

 Return the k-values corresponding to a sequence of pancake flips that sort A.  Any valid answer that sorts the array within 10 * A.length flips will be judged as correct.

  

 Example 1:

 Input: [3,2,4,1]
 Output: [4,2,4,3]
 Explanation:
 We perform 4 pancake flips, with k values 4, 2, 4, and 3.
 Starting state: A = [3, 2, 4, 1]
 After 1st flip (k=4): A = [1, 4, 2, 3]
 After 2nd flip (k=2): A = [4, 1, 2, 3]
 After 3rd flip (k=4): A = [3, 2, 1, 4]
 After 4th flip (k=3): A = [1, 2, 3, 4], which is sorted.
 Example 2:

 Input: [1,2,3]
 Output: []
 Explanation: The input is already sorted, so there is no need to flip anything.
 Note that other answers, such as [3, 3], would also be accepted.
 
 
 
 
 */

#include <vector>
using std::vector;

class PancakeSort {


    vector<int> doit_(vector<int>& arr) {
        // NOTE : each iter find the largest num, say at idx
        //.       Flip [0,idx]. This brings largest num to [0].
        //.       Then flip [0,n-iter] to get the largest num in its place.

        auto find = [&](int v, int b, int e) {
            for(int i=b; i<e; ++i) {
                if (arr[i]==v) return i;
            }
            return -1;
        };

        int n=arr.size();
        vector<int> res;
        for(int i=n, idx; i>=1; --i) {
            // find i in [0, i)
            idx = find(i, 0, i);
            for(int a=0, b=idx; a<b; ++a, --b) std::swap(arr[a], arr[b]);
            res.push_back(idx+1);
            // brings next largest number i.e i into its place
            for(int a=0, b=(i-1); a<b; ++a, --b) std::swap(arr[a], arr[b]);
            res.push_back(i);
        }
        return res;
    }

    /*
        """
        for case [3,2,4,1], we can flip to [1, 2, 3, 4] like below ways. 
        We finsh from n ~ 1. Each time, if number n is not in index n-1, it will be a target to do. Saying number n is on the pos k,
        Since we only can flip from 0 ~ k, that means  flip[0:k], then n will be on pos[0],  like [3, 2, 4, 1] => [4, 2, 3, 1]
        Thne n is getting into index 0, then we need to flip[0:n], so n will reach to its position. [4, 2, 3, 1] => [1, 3, 2, 4]

        then we go over the array back to forth, then finish each number i. if i is already in ith pos, then no need to change,
        or if num i in j, it need to do flip[0:j] and then flip[0:i] 
    */    
    vector<int> doit_flip(vector<int>& arr) {
        
        auto flip = [&](int k) {
            for (int i = 0, j = k; i < j; i++, j--)
                std::swap(arr[i], arr[j]);
        };
        
        vector<int> ans;
        int cur = arr.size();
        while (cur > 0) {
            
            if (arr[cur-1] != cur) {
                
                if (arr[0] != cur) {
                    int index = 0;
                    while (index < arr.size() && arr[index] != cur) index++;
                    flip(index);
                    ans.push_back(index+1);
                }
                
                flip(cur-1);
                ans.push_back(cur);
            }
            cur--;
        }
        
        return ans;
    }

    
    void rev(vector<int>&v,int r)
    {
        int i;
        for(i=0;i<=r/2;i++)
        {
            int b=v[i];
            v[i]=v[r-i];
            v[r-i]=b;
        }
        return;
    }
    
    vector<int> doit2 (vector<int>& A) {
        int i,j,k,n=A.size();
        vector<int>v;
        for(i=n;i>=2;i--)
        {
            for(j=0;j<n;j++)
            {
                if(A[j]==i)
                    break;
            }
            if((j+1)!=i)
            {
                v.push_back(j+1);
                rev(A,j);
                rev(A,i-1);
                v.push_back(i);
            }
        }
        return v;
    }
    
public:
    
    vector<int> doit(vector<int>&& A) {
    
        int N = A.size();
        
        vector<int> ans;
        for (int x = N; x > 1; x--) {
            
            vector<int> next(A);
            int i = 0;
            while (i < N && A[i] != x)
                i++;
            
            ans.push_back(i+1);
            ans.push_back(x);
            
            if (i+1 == x)
                continue;
 
            
            // move 0 ~ i to x - i -1  ~ x - 1, (i+1)
            for (int j = i; j > -1; j--) {
                A[x - 1 - i + j]= next[j];
            }
            
            // move i + 1 ~ x - 1 to 0 ~ x - i - 1 by reverse, (x - i - 1))
            for (int j = i + 1; j < x; j++) {
                A[x - j - 1] = next[j];
            }
        }
        
        return ans;
    }
};


void test_969_pancake_sorting() {
    
    auto res1 = PancakeSort().doit(vector<int>{3,2,4,1});
    
    auto res2 = PancakeSort().doit(vector<int>{1,2,3});
    
    auto res3 = PancakeSort().doit(vector<int>{3,1,2});
    
    return;
}
