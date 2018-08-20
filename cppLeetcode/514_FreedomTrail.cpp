


/*




# 514. Freedom Trail

# In the video game Fallout 4, the quest "Road to Freedom" requires players to reach a metal dial called the "Freedom Trail Ring",
# and use the dial to spell a specific keyword in order to open the door.

# Given a string ring, which represents the code engraved on the outer ring and another string key,
# which represents the keyword needs to be spelled. You need to find the minimum number of steps in order to spell all the characters in the keyword.

# Initially, the first character of the ring is aligned at 12:00 direction.
# You need to spell all the characters in the string key one by one by rotating the ring clockwise or anticlockwise to make each character of the string key aligned at 12:00 direction and then by pressing the center button.
# At the stage of rotating the ring to spell the key character key[i]:
# You can rotate the ring clockwise or anticlockwise one place, which counts as 1 step.
# The final purpose of the rotation is to align one of the string ring's characters at the 12:00 direction,
# where this character must equal to the character key[i].

# If the character key[i] has been aligned at the 12:00 direction, you need to press the center button to spell, which also counts as 1 step.
# After the pressing, you could begin to spell the next character in the key (next stage), otherwise, you've finished all the spelling.
# Example:



# Input: ring = "godding", key = "gd"
# Output: 4
# Explanation:
# For the first key character 'g', since it is already in place, we just need 1 step to spell this character.
# For the second key character 'd', we need to rotate the ring "godding" anticlockwise by two steps to make it become "ddinggo".
# Also, we need 1 more step for spelling.
# So the final output is 4.



*/

#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

class FindRotateSteps {
public:
	int doit (string ring, string key) {

		int rlength = ring.length();
		int klength = key.length();
		unordered_map<char, vector<int>> mp;
		for (auto c = 0; c < ring.length(); c++) {
			mp[ring[c]].push_back(c);
		}

		vector<vector<int>> dp(klength + 1, vector<int>(rlength, INT_MAX));
		std::fill(dp[0].begin(), dp[0].end(), 0);
		vector<int> tmp(1, 0);
		int res = INT_MAX;

		for (auto i = 1; i <= key.length(); i++) {

			for (auto j : mp[key[i - 1]]) {

				for (auto z = 0; z < tmp.size(); z++) {
					int minDist = std::min(abs(tmp[z] - j), rlength - abs(tmp[z] - j)) + dp[i - 1][tmp[z]];
					dp[i][j] = std::min(dp[i][j], minDist);
					res = (i != klength ? res : min(res, dp[i][j]));
				}
			}

			tmp = mp[key[i - 1]];
		}
	
		return res + klength;
	}

	int doit1(string ring, string key) {

		int rlength = ring.length();
		int klength = key.length();
		vector<vector<int>> mp(26);

		for (auto i = 0; i < rlength; i++) {
			mp[ring[i] - 'a'].push_back(i);
		}

		vector<int> start(1, 0);
		vector<int> dp(rlength, INT_MAX);
		dp[0] = 0;

		for (auto i = 0; i < klength; i++) {
			vector<int> nextDP(rlength, INT_MAX);
			for (auto j : mp[key[i] - 'a']) {
				for (auto z : start) {
					int misDistance = std::min(abs(z - j), rlength - abs(z - j)) + dp[z];
					nextDP[j] = std::min(nextDP[j], misDistance);
				}
			}
			start = mp[key[i] - 'a'];
			dp = nextDP;
		}

		auto cmin = INT_MAX;
		for (auto c : dp) {
			cmin = std::min(cmin, c);
		}

		return cmin + klength;
	}
};


void Test_514_FreedomTrail() {

	auto res = FindRotateSteps().doit("godding", "gd");

	res = FindRotateSteps().doit1("godding", "gd");

	return;
}






//class FindRotateSteps {
//
//	typedef struct { int r, k; } P;
//
//	typedef unordered_map<char, vector<int>> CHAR_TO_POS;
//
//	typedef unordered_map<P, int> DPBuff;
//
//	
//
//	int search(CHAR_TO_POS pos, string& ring, int rIdx, string& key, int kIdx, DPBuff& D) {
//
//		P idxPair{ rIdx, kIdx };
//		if (D.find(idxPair) != D.end())
//			return D[idxPair];
//
//		if (kIdx == key.length())
//			return 0;
//		
//		int res = INT_MAX;
//		for (auto c : pos[rIdx]) {
//
//			int step = std::min(static_cast<size_t> (abs(c - rIdx)), ring.size() - abs(c - rIdx));
//
//			res = std::min(res, step + search(pos, ring, c, key, kIdx + 1, D));
//
//		}
//
//		D[idxPair] = res + 1;
//
//		return D[idxPair];
//
//
//	}
//
//public:
//	int doit(string ring, string key) {
//
//
//		CHAR_TO_POS charDict;
//		for (auto i = 0; i < ring.length(); i++) {
//			charDict[ring[i]].push_back(i);
//		}
//
//		DPBuff D;
//
//		return search(charDict, ring, 0, key, 0, D);
//	}
//};

