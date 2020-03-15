mod leetcode_easy;
mod leetcode_media;
mod leetcode_hard;

fn main() {
    println!("Hello, world!");

    leetcode_easy::binary_tree::test_binary_tree();

    leetcode_media::A967_NumbersWithSameConsecutiveDifferences::test_967_NumbersWithSameConsecutiveDifference();

    leetcode_media::A978_LongestTurbulentSubarray::test_978_max_turbulence_size();

    leetcode_media::A974_SubarraySumsDivisibleByK::test_974_subarray_sums_divisible_by_k();

    leetcode_hard::A960_DeleteColumnsToMakeSortedIII::test_960_delete_columns_to_make_sortedIII();
}

