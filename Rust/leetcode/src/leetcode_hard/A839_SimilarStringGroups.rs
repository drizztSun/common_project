/*

# 839. Similar String Groups

# Two strings X and Y are similar if we can swap two letters (in different positions) of X, so that it equals Y.

# For example, "tars" and "rats" are similar (swapping at positions 0 and 2), and "rats" and "arts" are similar,
# but "star" is not similar to "tars", "rats", or "arts".

# Together, these form two connected groups by similarity: {"tars", "rats", "arts"} and {"star"}.

# Notice that "tars" and "arts" are in the same group even though they are not similar.
# Formally, each group is such that a word is in the group if and only if it is similar
# to at least one other word in the group.

# We are given a list A of unique strings.  Every string in A is an anagram of every other string in A.
# How many groups are there?

# Example 1:

# Input: ["tars","rats","arts","star"]
# Output: 2
# Note:

# A.length <= 2000
# A[i].length <= 1000
# A.length * A[i].length <= 20000
# All words in A consist of lowercase letters only.
# All words in A have the same length and are anagrams of each other.
# The judging time limit has been increased for this question.

*/

mod num_similar_groups {

    //use std::vec;

    struct Dsu {
        parent_: Vec<usize>,
        size_: usize,
    }

    impl Dsu {
        fn new(n: usize) -> Dsu {
            Dsu {
                size_: n,
                parent_: Vec::with_capacity(n),
            }
        }

        fn find(&mut self, a: usize) -> usize {
            let mut base = a;
            while self.parent_[base] != a {
                self.parent_[base] = self.parent_[self.parent_[base]];
                base = self.parent_[base];
            }

            return base;
        }

        fn union(&mut self, a: usize, b: usize) {
            let pa = self.find(a);
            let pb = self.find(b);

            self.parent_[pa] = pb;
            self.size_ -= 1;
        }
    }

    pub fn doit(a: Vec<String>) -> i32 {
        let mut d = Dsu::new(a.len());

        let similar = |A: &String, B: &String| {
            let pa: Vec<_> = A.chars().collect();
            let pb: Vec<_> = B.chars().collect();
            let mut res: i32 = 0;
            if pa.len() != pb.len() {
                return false;
            }

            for i in 1..pa.len() - 1 {
                if pa[i] != pb[i] {
                    res += 1;
                }
            }

            return res == 2;
        };

        for i in 1..a.len() - 1 {
            for j in i + 1..a.len() - 1 {
                if similar(&a[i], &a[j]) {
                    d.union(i, j);
                }
            }
        }

        return (a.len() - d.size_) as i32;
    }
}

pub fn test_839_similar_string_groups() {
    let _res = num_similar_groups::doit(vec![
        "tars".to_string(),
        "rats".to_string(),
        "arts".to_string(),
        "star".to_string(),
    ]);
}
