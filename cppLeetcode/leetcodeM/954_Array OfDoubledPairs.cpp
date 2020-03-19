/*
 
 
 954. Array of Doubled Pairs
 
 Given an array of integers A with even length, return true if and only if it is possible to reorder it such that A[2 * i + 1] = 2 * A[2 * i] for every 0 <= i < len(A) / 2.

  

 Example 1:

 Input: [3,1,3,6]
 Output: false
 Example 2:

 Input: [2,1,2,6]
 Output: false
 Example 3:

 Input: [4,-2,2,-4]
 Output: true
 Explanation: We can take two groups, [-2,-4] and [2,4] to form [-2,-4,2,4] or [2,4,-2,-4].
 Example 4:

 Input: [1,2,4,16,8,4]
 Output: false
 
 */

#include <vector>
using std::vector;

#include <unordered_map>
using std::unordered_map;

#include <cmath>

#include <unordered_set>
using std::unordered_set;

#include <map>
using std::map;

class CanReorderDoubled {
    
public:
    
    bool doit1(vector<int>&& A) {
    
        unordered_map<int, int> buf;
        for (auto c : A) {
            buf[c]++;
        }
        
        std::sort(A.begin(), A.end(), [](auto a, auto b) {
            return std::abs(a) < std::abs(b);
        });
        
        for (auto c : A) {
            
            if (buf[c] == 0)
                continue;
            
            if (buf[c * 2] == 0)
                return false;
            
            buf[c]--;
            buf[c * 2]--;
        }
        
        return true;
    }
    
    bool doit2(vector<int>& A) {
        map<int,int> m;
        for(auto &x:A)
            m[x]++;
        
        for(auto &i: m){
            if(m.find(2*i.first) != m.end()){
                int y = std::min(i.second, m[2*i.first]);
                m[2*i.first]-=y;
                m[i.first]-=y;
            }
        }
        
        for(auto &i:m){
            if(i.second>0)
                return false;
        }
        
        return true;
    }
    
    bool doit(vector<int>&& A) {
        
        unordered_map<int, int> buf;
        unordered_set<int> groups;
        for (auto c : A) {
            buf[c]++;
            groups.insert(c);
        }
        
        vector<int> nums;
        for (auto c : groups) {
            nums.push_back(c);
        }
        
        std::sort(nums.begin(), nums.end());
        
        for (auto c: nums) {
            
            if (c < 0 && c % 2 == 0 && buf.count(c / 2) != 0 && buf[c/2] > 0) {
                buf[c/2] -= buf[c];
                buf[c] = 0;
            } else if (c > 0 && buf.count(c * 2) != 0 && buf[c * 2] > 0) {
                buf[c * 2] -= buf[c];
                buf[c] = 0;
            }
        }
        
        for (auto& c : buf) {
            if (c.second != 0)
                return false;
        }
        
        return true;
    }
};


void test_954_array_of_double_pairs() {
    
    auto res1 = CanReorderDoubled().doit(vector<int>{3,1,3,6});
    
    auto res2 = CanReorderDoubled().doit(vector<int>{2,1,2,6});
    
    auto res3 = CanReorderDoubled().doit(vector<int>{4,-2,2,-4});
    
    auto res4 = CanReorderDoubled().doit(vector<int>{1,2,4,16,8,4});
    
    auto res5 = CanReorderDoubled().doit(vector<int>{-8,-4,-2,-1,0,0,1,2,4,8});

    return;
}
