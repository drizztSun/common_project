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

    use std::vec;

    pub fn doit(a: Vec<i32>) -> i32 {

        let B: Vec<i32> = [1..a.len()];

        B.sort_by(|i, j| {
            return a[i] < a[j];
        });

        

        return 0;
    }
}

pub fn test_962_maximum_width_ramp() {

    let res1 = max_width_ramp::doit(vec![6,0,8,2,1,5]);

    let res2 = max_width_ramp::doit(vec![9,8,1,0,1,9,4,0,4,1]);

    return;
}