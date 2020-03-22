/*
 
 
 967. Numbers With Same Consecutive Differences
 
 Return all non-negative integers of length N such that the absolute difference between every two consecutive digits is K.

 Note that every number in the answer must not have leading zeros except for the number 0 itself.
 For example, 01 has one leading zero and is invalid, but 0 is valid.

 You may return the answer in any order.

  

 Example 1:

 Input: N = 3, K = 7
 Output: [181,292,707,818,929]
 Explanation: Note that 070 is not a valid number, because it has leading zeroes.
 Example 2:

 Input: N = 2, K = 1
 Output: [10,12,21,23,32,34,43,45,54,56,65,67,76,78,87,89,98]
  
 
 */

#include <vector>
using std::vector;

class NumsSameConsecDiff {
    
    /*
     Approach 1: Brute Force
     Intuition

     Let's try to write some number in the answer digit by digit.

     For each digit except the first, there are at most 2 choices for that digit. This means that there are at most 9 * 2^89∗2
     8
       possible 9 digit numbers, for example. This is small enough to brute force.

     Algorithm

     An NN digit number is just an N-1N−1 digit number with a final digit added. If the N-1N−1 digit number ends in a digit dd, then the NN digit number will end in d-Kd−K or d+Kd+K (provided these are digits in the range [0,9][0,9]). We store these numbers in a Set structure to avoid duplicates.

     Also, we should be careful about leading zeroes -- only 1 digit numbers will start with 0.
     */
    
public:
    vector<int> doit(int N, int K) {
    
        vector<int> ans{1, 2, 3, 4, 5, 6, 7, 8, 9};
        
        for (int i = 1; i < N; i++) {
            vector<int> tmp;
            for (auto c = ans.begin(); c != ans.end(); c++) {
                
                int last = *c % 10;
                
                if (K != 0) {
                    if (last - K > -1)
                        tmp.push_back(*c * 10 + last - K);
                    
                    if (last + K < 10)
                        tmp.push_back(*c * 10 + last + K);
                } else
                    tmp.push_back(*c * 10 + last);

            }
            swap(ans, tmp);
        }
        
        return ans;
    }
    
    vector<int> doit1(int N, int K) {
        vector<int> result;
        if (N == 1) result.push_back(0);
        for (int i = 1; i < 10; ++i) {
            myFunc(result, 0, i, K, N - 1);
        }
        return result;
    }
    
    void myFunc(vector<int>& result, int val, int currDigit, int K, int N){
        if (currDigit >= 10 || currDigit < 0) return;
        
        val = val * 10 + currDigit;
        if (N == 0) {
            result.push_back(val);
            return;
        }
        
        myFunc(result, val, currDigit + K, K, N - 1);
        if (K != 0)
            myFunc(result, val, currDigit - K, K, N - 1);
    }
};


void test_967_numbers_with_same_consecutive_difference() {
    
    auto res1 = NumsSameConsecDiff().doit(3, 7);
    
    auto res2 = NumsSameConsecDiff().doit(2, 1);
    
    auto res3 = NumsSameConsecDiff().doit(2, 0);
    
    return;
}
