
mod max_turbulence_size {

    use std::vec;
    use std::cmp::max;

    pub fn doit1(a: Vec<i32>) -> i32 {
        let n = a.len();
        let mut ans = 1;
        let mut f = 1;
        let mut g = 1;

        for i in 1..n {
            if a[i] > a[i-1] {
                f = g + 1;
                g = 1;
                ans = ans.max(f);
            } else if a[i] < a[i-1] {
                g = f + 1;
                f = 1;
                ans = ans.max(g);
            } else {
                f = 1;
                g = 1;
            }
        }
        ans
    }

    pub fn doit2(a: Vec<i32>) -> i32 {

        let mut ans = 1;
        let mut length = 1;

        for i in 1..a.len() {
            
            if (i > 1 && ((a[i-1] > a[i] && a[i-1] > a[i-2]) || (a[i-1] < a[i] && a[i-1] < a[i-2]))) {
                length += 1;
            } else if a[i] != a[i-1] {
                length = 2;
            } else {
                length = 1;
            }
            ans = max(ans, length);
        }
        
        return ans;
    }
}

pub fn test_978_max_turbulence_size() {

    let res = max_turbulence_size::doit1(vec![1, 2, 3]);
}