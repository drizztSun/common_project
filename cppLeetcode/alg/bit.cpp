#include <vector>
#include <algorithm>

using std::vector;

const int MAX_N = 100000;

class Solution {
public:    
    long long bitArr[MAX_N+1];
    long long nums[MAX_N+1];  // Note: nums is 1-index
    long long M = 1e9+7;

    // increase nums[i] by delta  (1-index)
    void updateDelta(int i, long long delta) {
        int idx = i;
        while (idx <= MAX_N)
        {
            bitArr[idx]+=delta;
            bitArr[idx] %= M;
            idx+=idx&(-idx);
        }
    }

    // sum of a range nums[1:j] inclusively, 1-index
    long long queryPreSum(int idx){
        long long result = 0;
        while (idx){
            result += bitArr[idx];
            result %= M;
            idx-=idx&(-idx);
        }
        return result;
    }

    // sum of a range nums[i:j] inclusively
    long long sumRange(int i, int j) {    
        return queryPreSum(j)-queryPreSum(i-1);
    }    
};

vector<int> doit_BIT(vector<int>& nums) {
    int maxv = *max_element(begin(nums), end(nums));
    int min_val = *min_element(begin(nums), end(nums));
    // vector<int> bit(100002,0);
    vector<int> bit(maxv - min_val + 10, 0);
    vector<int> output(nums.size());

    auto get = [&](int index) -> int {
        index++;
        int val=0;
        while(index>=1) {
            val+=bit[index];
            index-=index&-index;
        }
        return val;
    };
    
    auto update = [&](int index,int val) {
        index++;
        while(index<bit.size()) {
            bit[index]+=val;
            index+=index&-index;
        }
    };

    for(int i = nums.size()-1; i >=0; i--)
    {
        if(min_val<0) nums[i] += (-min_val+1);

        int count = get(nums[i]-1);
    
        output[i] = count;
        
        update(nums[i],1);
    }
    return output;
}