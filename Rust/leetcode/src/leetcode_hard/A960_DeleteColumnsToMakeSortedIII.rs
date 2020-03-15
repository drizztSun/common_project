
mod delete_columns_to_make_sorted_iii {

    use std::vec;
    use std::cmp::max;

    pub fn doit(a: Vec<String>) -> i32 {

        let mut dp = Vec::with_capacity(a[0].len());
        let col: i32 = a[0].len();

        for i in (0..col-2).rev() {

            for j in (i+1..col-1) {

                let mut cnt = 0;
                for word in a.iter() {
                    //if word.chars()[i] > word[j] {
                    //    break;
                    //}
                    cnt += 1;
                }
                if cnt == a.len() {
                    //dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        return col;
    }
}

pub fn test_960_delete_columns_to_make_sortedIII() {

    let res1 = delete_columns_to_make_sorted_iii::doit(vec!["babca","bbazb"]);

    let res2 = delete_columns_to_make_sorted_iii::doit(vec!["edcba"]);

    let res3 = delete_columns_to_make_sorted_iii::doit(vec!["ghi","def","abc"]);

    return;
}