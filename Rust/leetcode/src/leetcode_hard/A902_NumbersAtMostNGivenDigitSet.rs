/*

We have a sorted set of digits D, a non-empty subset of {'1','2','3','4','5','6','7','8','9'}.  (Note that '0' is not included.)

Now, we write numbers using these digits, using each digit as many times as we want.  For example, if D = {'1','3','5'}, we may write numbers such as '13', '551', '1351315'.

Return the number of positive integers that can be written (using the digits of D) that are less than or equal to N.



Example 1:

Input: D = ["1","3","5","7"], N = 100
Output: 20
Explanation:
The 20 numbers that can be written are:
1, 3, 5, 7, 11, 13, 15, 17, 31, 33, 35, 37, 51, 53, 55, 57, 71, 73, 75, 77.
Example 2:

Input: D = ["1","4","9"], N = 1000000000
Output: 29523
Explanation:
We can write 3 one digit numbers, 9 two digit numbers, 27 three digit numbers,
81 four digit numbers, 243 five digit numbers, 729 six digit numbers,
2187 seven digit numbers, 6561 eight digit numbers, and 19683 nine digit numbers.
In total, this is 29523 integers that can be written using the digits of D.

*/
use std::vec::Vec;

mod at_most_n_given_digit_set {

    pub fn doit(d: Vec<String>, n: i32) -> i32 {
        let mut nums: Vec<i8> = Vec::with_capacity(d.len());
        for c in d.iter() {
            let num = c.parse::<i8>().unwrap();
            nums.push(num);
        }

        nums.sort_by(|i, j| i.cmp(j));

        let mut bits = Vec::new();
        let mut num = n;
        while num > 0 {
            bits.push((num % 10) as i8);
            num /= 10;
        }

        let mut dp: Vec<u32> = vec![0; bits.len() + 1];
        dp[0] = 1;
        let m = nums.len() as u32;

        let mut base: u32 = 0;
        for i in (1..bits.len()) {
            base += m.pow(i as u32)
        }

        for i in (0..bits.len()) {
            for c in nums.iter() {
                if *c < bits[i] {
                    dp[i + 1] += m.pow(i as u32);
                } else if *c == bits[i] {
                    dp[i + 1] += dp[i];
                }
            }
        }

        return (dp[bits.len()] + base) as i32;
    }
}

pub fn test_902_nmbers_at_most_ngiven_digits_set() {
    let res = at_most_n_given_digit_set::doit(vec![String::from("3"), String::from("5")], 4);

    let _res = at_most_n_given_digit_set::doit(
        vec![
            String::from("1"),
            String::from("3"),
            String::from("5"),
            String::from("7"),
        ],
        100,
    );

    let _res1 = at_most_n_given_digit_set::doit(
        vec![String::from("1"), String::from("4"), String::from("9")],
        1000000000,
    );

    println!("End");
}
