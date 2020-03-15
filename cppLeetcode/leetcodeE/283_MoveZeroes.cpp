/*
 
 
 283. Move Zeroes
 
 Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.

 Example:

 Input: [0,1,0,3,12]
 Output: [1,3,12,0,0]
 
 */

#include <vector>
using std::vector;

class MoveZeroes {
    
public:
    
    void doit(vector<int>& nums) {
        
        int j = 0;
        
        for (int i = 0; i < nums.size() && j < nums.size(); i++) {
            
            if (j <= i) {
                while (j < nums.size() && nums[j] != 0) {
                    j++;
                }
            }
            
            if (nums[i] != 0 && i > j) {
                nums[j] = nums[i] ;
                nums[i] = 0;
                j++;
            }
        }
    }
};


void test_283_move_zones() {
    
    vector<int> nums{0,1,0,3,12};
    
    MoveZeroes().doit(nums);

    return;
}
