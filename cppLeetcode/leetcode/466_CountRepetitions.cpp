

/*

	466. Count The Repetitions

	It’s easy to come up with a brute force solution and to find that there will be a repetitive pattern
	when matching S2 through S1. The only problem is how to use the repetitive pattern to save computation.

	Fact:
	If s2 repeats in S1 R times, then S2 must repeats in S1 R / n2 times.
	Conclusion:
	We can simply count the repetition of s2 and then divide the count by n2.

	How to denote repetition:
	We need to scan s1 n1 times. Denote each scanning of s1 as a s1 segment.
	After each scanning of i-th s1 segment, we will have

	The accumulative count of s2 repeated in this s1 segment.
	A nextIndex that s2[nextIndex] is the first letter you’ll be looking for in the next s1 segment.
	Suppose s1="abc", s2="bac", nextIndex will be 1; s1="abca", s2="bac", nextIndex will be 2

	It is the nextIndex that is the denotation of the repetitive pattern.


	Example:

	Input:
	s1="abacb", n1=6
	s2="bcaa", n2=1

	Return:
	3
						0  1   2 3 0      1    2 3 0      1    2 3 0
	S1 --------------> abacb | abacb | abacb | abacb | abacb | abacb
	repeatCount ----->    0  |   1   |   1   |   2   |   2   |   3
	Increment of
	repeatCount     ->    0  |   1   |   0   |   1   |   0   |   1
	nextIndex ------->    2  |   1   |   2   |   1   |   2   |   1
	The nextIndex has s2.size() possible values, ranging from 0 to s2.size() - 1. Due to PigeonHole principle, you must find two same nextIndex after scanning s2.size() + 1 s1 segments.

	Once you meet a nextIndex you’ve met before, you’ll know that the following nextIndexs and increments of repeatCount will repeat a pattern.

	So let’s separate the s1 segments into 3 parts:

	the prefix part before repetitive pattern
	the repetitive part
	the suffix part after repetitive pattern (incomplete repetitive pattern remnant)
	All you have to do is add up the repeat counts of the 3 parts.
*/

#include <string>
using namespace std;

class MaxRepetitions {
public:
	int doit(string s1, int n1, string s2, int n2) {



        return 0;
	}
};
