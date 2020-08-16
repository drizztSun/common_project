//use std::vec;

mod num_perms_di_sequence {

    fn search(s: &String, i: i32, j: i32, dp: &mut Vec<Vec<i32>>) -> i32 {
        if !(j >= 0 && j <= i) {
            return 0;
        }

        if dp[i as usize][j as usize] != 0 {
            return dp[i as usize][j as usize];
        }

        if i == 0 {
            return 1;
        }

        let mut res = 0;

        if s.as_bytes()[(i - 1) as usize] == 'D' as u8 {
            res = (search(s, i, j + 1, dp) + search(s, i - 1, j, dp)) % 1000000007;
        } else {
            res = (search(s, i, j - 1, dp) + search(s, i - 1, j - 1, dp)) % 1000000007;
        }

        dp[i as usize][j as usize] = res;
        return res;
    }

    pub fn doit(s: String) -> i32 {
        let N = s.len();
        let mut dp = vec![vec![0; N + 1]; N + 1];
        let mut res = 0;

        for i in (0..N + 1).rev() {
            res = (res + search(&s, N as i32, i as i32, &mut dp)) % 1000000007;
        }

        return res % 1000000007;
    }
}

pub fn test_903_valid_permutation_for_Di_sequence() {
    num_perms_di_sequence::doit(String::from("IDDDIIDIIIIIIIIDIDID"));
    num_perms_di_sequence::doit(String::from("DID"));
}
