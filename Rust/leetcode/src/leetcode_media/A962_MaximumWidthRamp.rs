/*

962. Maximum Width Ramp

Given an array A of integers, a ramp is a tuple (i, j) for which i < j and A[i] <= A[j].  The width of such a ramp is j - i.

Find the maximum width of a ramp in A.  If one doesn't exist, return 0.



Example 1:

Input: [6,0,8,2,1,5]
Output: 4
Explanation:
The maximum width ramp is achieved at (i, j) = (1, 5): A[1] = 0 and A[5] = 5.
Example 2:

Input: [9,8,1,0,1,9,4,0,4,1]
Output: 7
Explanation:
The maximum width ramp is achieved at (i, j) = (2, 9): A[2] = 1 and A[9] = 1.

*/
mod max_width_ramp {

    use std::cmp;
    //use std::vec;

    pub fn doit(a: Vec<i32>) -> i32 {
        let mut B: Vec<usize> = (0..a.len()).collect();

        B.sort_by(|i, j| {
            return a[*i].cmp(&a[*j]);
        });

        let mut min_index: i32 = a.len() as i32;
        let mut ans: i32 = 0;
        for c in B.iter() {
            ans = cmp::max(ans, *c as i32 - min_index);
            min_index = cmp::min(*c as i32, min_index);
        }

        return ans;
    }

    pub fn doit1(a: Vec<i32>) -> i32 {
        let len = a.len();
        let max_rev: Vec<i32> = a
            .iter()
            .rev()
            .scan(0, |s, &x| {
                *s = std::cmp::max(*s, x);
                Some(*s)
            })
            .collect();

        /*
        let mut max: Vec<i32> = vec![a[len - 1]; len];
        for i in (0..len - 1).rev() {
            max[i] = std::cmp::max(max[i + 1], a[i]);
        }
        */
        let mut left = 0;
        let mut right = 0;
        let mut max_ramp = 0;
        while right < len {
            while left < right && a[left] > max_rev[len - right - 1] {
                left += 1;
            }
            max_ramp = std::cmp::max(max_ramp, right - left);
            right += 1;
        }
        max_ramp as i32
    }
}

pub fn test_962_maximum_width_ramp() {
    let _res1 = max_width_ramp::doit(vec![6, 0, 8, 2, 1, 5]);

    let _res2 = max_width_ramp::doit(vec![9, 8, 1, 0, 1, 9, 4, 0, 4, 1]);

    let _res3 = max_width_ramp::doit(vec![0, 1]);

    return;
}
