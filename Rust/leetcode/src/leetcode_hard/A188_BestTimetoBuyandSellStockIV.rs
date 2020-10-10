/*

188. Best Time to Buy and Sell Stock IV

*/
use std::cmp::max;

struct MaxStockProfitIV (u8);

impl MaxStockProfitIV {
    pub fn doit_dp(k: i32, prices: Vec<i32>) -> i32 {

        if prices.is_empty() {
            return 0;
        }
        
        let m = prices.len();
        let mut dp: Vec<Vec<i32>> = vec![vec![0; m as usize]; (k+1) as usize];
        let mut max_profit = 0;

        if k > (prices.len() / 2) as i32 {
            let mut ret = 0;
            for i in 1..prices.len() {
                if prices[i] > prices[i - 1] {
                    ret += prices[i] - prices[i - 1];
                }
            }
            return ret;
        }

        for i in 1..k+1 {

            let i: usize = i as usize;
            let mut tmp = dp[i-1][0] - prices[0];

            for j in 1..prices.len() {

                dp[i][j] = max(dp[i][j-1], tmp+prices[j]);

                tmp = max(tmp, dp[i-1][j] - prices[j]);

                max_profit = max(max_profit, dp[i][j]);
            }
        }
        return max_profit;
    }

    pub fn doit_dp_1(k: i32, prices: Vec<i32>) -> i32 {
        /*
        * dp[k][i]: the profit of k-transactions **finished** at i-th day
        * dp[k][i] = max(dp[k][i-1], max_j(prices[i] - prices[j] + dp[k-1][j-1])).
        *                  where j-1 <= i - 2, so j is in [0, i - 1]
        * dp[k][i] = max(dp[k][i-1], prices[i] + max_j(dp[k-1][j] - prices[j]))
        * optimize: compress at dimension k:
        *          dp[i] = max(dp[i-1], prices[i] + max_j(dp[j] - prices[j])
                         = max(dp[i-1], prices[i] + pre_max_gap)
        * optimize: as we can't transact more than once per day, for dp[k][i]
        *              , i start at 2*(k-1) + 1 = 2k - 1
        *          for example: k = 1, i >= 1
        *                       k = 2, i >= 3
        *                       k = 3, i >= 5
        * initial state:
        *          dp[0][..] = 0 , i.e.  dp[..] = 0
        */

        if k <= 0 || prices.is_empty() {
            return 0;
        }
        // optimize: k is so large, that we can maximize our benefits
        if k > (prices.len() / 2) as i32 {
            let mut ret = 0;
            for i in 1..prices.len() {
                if prices[i] > prices[i - 1] {
                    ret += prices[i] - prices[i - 1];
                }
            }
            return ret;
        }

        // k is not large enough, so we have to use dp to calculate
        let mut dp = vec![0; prices.len()];
        for kk in 1..=k {
            // start at 1
            // for dp[k-1][j-1]: j - 1 >= 2*(k-1) - 1 = 2k - 3, so j >= 2k - 2
            // and j <= i - 1, i >= 2k - 1 => j <= 2k - 2
            // so j is in [2k - 2, 2k - 2], so, j == 2k - 2 == i_start - 1
            let kk = kk as usize;
            let i_start = 2 * kk - 1;
            let j_start = i_start - 1; // always >= 0
            let mut max_gap = dp[j_start] - prices[j_start];
            for i in (2 * kk - 1)..prices.len() {
                let next_gap = dp[i] - prices[i];
                dp[i] = dp[i-1].max(prices[i] + max_gap);
                max_gap = max_gap.max(next_gap);
            }
        }
        dp[prices.len() - 1]
    }
}

pub fn test_188_best_time_to_buy_and_sell_stockiv() {

    MaxStockProfitIV::doit_dp(3, vec![1, 2, 3, 4, 5]);
}
