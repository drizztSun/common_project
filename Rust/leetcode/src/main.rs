mod leetcode_easy;
mod leetcode_media;

fn main() {
    println!("Hello, world!");

    leetcode_easy::binary_tree::test_binary_tree();

    leetcode_media::A967_NumbersWithSameConsecutiveDifferences::test_967_NumbersWithSameConsecutiveDifference();

    leetcode_media::A978_LongestTurbulentSubarray::test_978_max_turbulence_size();

    leetcode_media::A974_SubarraySumsDivisibleByK::test_974_subarray_sums_divisible_by_k();
}

