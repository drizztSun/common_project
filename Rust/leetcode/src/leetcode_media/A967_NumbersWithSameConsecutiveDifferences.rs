/*

967. Numbers With Same Consecutive Differences

Return all non-negative integers of length N such that the absolute difference between every two consecutive digits is K.

Note that every number in the answer must not have leading zeros except for the number 0 itself. For example, 01 has one leading zero and is invalid, but 0 is valid.

You may return the answer in any order.

 

Example 1:

Input: N = 3, K = 7
Output: [181,292,707,818,929]
Explanation: Note that 070 is not a valid number, because it has leading zeroes.
Example 2:

Input: N = 2, K = 1
Output: [10,12,21,23,32,34,43,45,54,56,65,67,76,78,87,89,98]

*/

use std::vec;
use std::collections::HashSet;

impl nums_same_consec_diff {

    pub fn doit(n: i32, k: i32) -> Vec<i32> {

        let mut ans : HashSet<i32> = [1, 2, 3, 4, 5, 6, 7, 8, 9].iter().cloned().collect();
        let mut i = 0;

        while i < n-1 {

            let mut ans2 = HashSet::new();

            for c in ans.iter() {

                let d = c % 10;

                if d - k > -1 {
                    ans2.insert(c * 10 + d - k);
                }

                if d + k < 10 {
                    ans2.insert(c * 10 + d + k);
                }
            }

            ans = ans2;

            i += 1
        }

        if n == 1 {
            ans.insert(0);
        }

        let mut res : Vec<i32> = Vec::new();

        for c in ans.iter() {
            res.push(c);
        }

        return res;
    }
}

pub fn test_967_NumbersWithSameConsecutiveDifference() {

    let res = nums_same_consec_diff::doit(3, 7);
}