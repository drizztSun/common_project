"""

444. Sequence Reconstruction

Check whether the original sequence org can be uniquely reconstructed from the sequences in seqs.
The org sequence is a permutation of the integers from 1 to n, with 1 ≤ n ≤ 104.
Reconstruction means building a shortest common supersequence of the sequences in seqs (i.e., a shortest sequence so that all sequences in seqs are subsequences of it).
Determine whether there is only one sequence that can be reconstructed from seqs and it is the org sequence.



Example 1:

Input: org = [1,2,3], seqs = [[1,2],[1,3]]
Output: false
Explanation: [1,2,3] is not the only one sequence that can be reconstructed, because [1,3,2] is also a valid sequence that can be reconstructed.
Example 2:

Input: org = [1,2,3], seqs = [[1,2]]
Output: false
Explanation: The reconstructed sequence can only be [1,2].
Example 3:

Input: org = [1,2,3], seqs = [[1,2],[1,3],[2,3]]
Output: true
Explanation: The sequences [1,2], [1,3], and [2,3] can uniquely reconstruct the original sequence [1,2,3].
Example 4:

Input: org = [4,1,5,2,6,3], seqs = [[5,2,6,3],[4,1,5,2]]
Output: true


Constraints:

1 <= n <= 10^4
org is a permutation of {1,2,...,n}.
1 <= segs[i].length <= 10^5
seqs[i][j] fits in a 32-bit signed integer.


"""
import itertools


class SequenceReconstruction:

    def doit_topsort(self, org: list, seqs: list):

        if not set(org) == set(itertools.chain(*seqs)):
            return False

        edges = {(org[i], org[i + 1]) for i in range(len(org) - 1)}
        pos = {c: i for i, c in enumerate(org)}

        for c in seqs:

            for i in range(len(c) - 1):

                if pos[c[i]] >= pos[c[i + 1]]:
                    return False

                # if (c[i], c[i+1]) in edges:
                edges.discard((c[i], c[i + 1]))

        return len(edges) == 0

    def doit_topsort(self, org: list, seqs: list):

        rank = [-1 for _ in range(len(org))]
        pos = {c: i for i, c in enumerate(org)}
        level = 0

        for i in range(len(seqs)):
            for c in seqs[i]:

                rank[pos[c]] = max(rank[pos[c]], l)
                l += 1

            level += 1







if __name__ == '__main__':

    SequenceReconstruction().doit_topsort(org = [1,2,3], seqs = [[1,2],[1,3]])

    SequenceReconstruction().doit_topsort(org = [1,2,3], seqs = [[1,2]])

    SequenceReconstruction().doit_topsort(org = [1,2,3], seqs = [[1,2],[1,3],[2,3]])

    SequenceReconstruction().doit_topsort(org = [4,1,5,2,6,3], seqs = [[5,2,6,3],[4,1,5,2]])