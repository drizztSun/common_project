mod subarrays_div_by_k {

    use std::collections::HashMap;

    pub fn doit(a: Vec<i32>, k: i32) -> i32 {
        let mut cache: HashMap<i32, i32> = HashMap::new();
        let mut total: i32 = 0;

        for c in a {
            total += c;
            let mut r = total % k;
            if r < 0 {
                r += k;
            }
            let cnt = cache.entry(r).or_insert(0);
            *cnt += 1
        }

        let mut ans = 0;
        for (k, v) in &cache {
            if *k == 0 {
                ans += v * (v + 1) / 2;
            } else {
                ans += v * (v - 1) / 2;
            }
        }
        return ans;
    }

    pub fn doit1(a: Vec<i32>, k: i32) -> i32 {
        let mut mod_map = HashMap::new();
        mod_map.insert(0, 1);

        let mut result = 0;
        let mut sum = 0;
        for i in a {
            sum = (sum + i) % k;
            if sum < 0 {
                sum += k
            }
            let has_count = mod_map.entry(sum).or_insert(0);
            result += *has_count;
            *has_count += 1;
        }
        result
    }
}

pub fn test_974_subarray_sums_divisible_by_k() {
    let _res = subarrays_div_by_k::doit(vec![4, 5, 0, -2, -3, 1], 5);

    let _res1 = subarrays_div_by_k::doit(vec![-1, 2, 9], 2);

    let _res2 = subarrays_div_by_k::doit(vec![2, -2, 2, -4], 6);
}
