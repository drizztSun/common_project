//
//  main.cpp
//  cppconsole
//
//  Created by Yuxin Sun on 3/15/20.
//  Copyright © 2020 Yuxin Sun. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using std::vector;

void TestUnorderMap();

void Test_Unordered_set();

void test_vector_morden_cpp();

void Test_share_ptr();

void test_constrexpr();

void test_deque();

void test_stack();

void Test_move_forward();

void Test_value_categories();

void Test_fold_expression();

void Test_type_deduce();

void test_basic();

void test_async();

void test_function_able();

void Test_priority_queue();

void TestUnorderMap();

void Test_map();

bool canPartition(vector<int>&& nums) {
    int sums = accumulate(begin(nums), end(nums), 0);
    if (sums % 2 == 1) return false;
    
    int half = sums/2;
    vector<int> dp(half+1, false);
    dp[0] = true;
    
    for (auto c: nums) {
        for (int i = 0; i <= half-c; i++) {
            if (dp[i]) {
                dp[i+c] = true;
            }
        }
        
        //if (dp[half]) return true;
    }
    
    return dp[half];
}

int main(int argc, const char * argv[]) {

    std::cout << "Hello, World!\n";
    
    canPartition(vector<int>{1, 2, 5});
    
    vector<int> A{1,1,1,0,0,0,1,1,1,1,0};
    int K = 2;
    int left = 0, right = 0;
    
    for (; right < A.size(); right++) {
        
        K -= 1 - A[right];
            
        if (K < 0) {
            K += 1 - A[left];
            left++;
        }
    }
    
    return right - left + 1;
    
    
    // Test_map();
    
    // TestUnorderMap();
    
    // Test_priority_queue();
    
    // test_function_able();
    
    // test_basic();
    
    // Test_type_deduce();
    
    // Test_fold_expression();
    
    // Test_value_categories();
    
    // Test_move_forward();

    // TestUnorderMap();

    // Test_Unordered_set();

    // test_vector_morden_cpp();

    // Test_share_ptr();
    
    // test_constrexpr();
    
    // test_deque();
    
    // test_stack();
    
    // test_async();

    return 1;
}

