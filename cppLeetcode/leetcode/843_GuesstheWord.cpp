/*

# 843. Guess the Word

# This problem is an interactive problem new to the LeetCode platform.

# We are given a word list of unique words, each word is 6 letters long, and one word in this list is chosen as secret.

# You may call master.guess(word) to guess a word.  The guessed word should have type string and must be from the original list with 6 lowercase letters.

# This function returns an integer type, representing the number of exact matches (value and position) of your guess to the secret word.  Also, if your guess is not in the given wordlist, it will return -1 instead.

# For each test case, you have 10 guesses to guess the word. At the end of any number of calls, if you have made 10 or less calls to master.guess and at least one of these guesses was the secret, you pass the testcase.

# Besides the example test case below, there will be 5 additional test cases, each with 100 words in the word list.  The letters of each word in those testcases were chosen independently at random from 'a' to 'z', such that every word in the given word lists is unique.

# Example 1:
# Input: secret = "acckzz", wordlist = ["acckzz","ccbazz","eiowzz","abcczz"]

# Explanation:

# master.guess("aaaaaa") returns -1, because "aaaaaa" is not in wordlist.
# master.guess("acckzz") returns 6, because "acckzz" is secret and has all 6 matches.
# master.guess("ccbazz") returns 3, because "ccbazz" has 3 matches.
# master.guess("eiowzz") returns 2, because "eiowzz" has 2 matches.
# master.guess("abcczz") returns 4, because "abcczz" has 4 matches.

# We made 5 calls to master.guess and one of them was the secret, so we pass the test case.
# Note:  Any solutions that attempt to circumvent the judge will result in disqualification.

# """
# This is Master's API interface.
# You should not implement it, or speculate about its implementation
# """


*/

#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <unordered_map>
#include <iostream>
using namespace std;


class Master {

    string secret_;
    int times_;

public:

    Master(const string& secret) : 
		secret_(secret), times_(0)
    {

    }


    int guess(const string& guessStr) {

        int size = 0;
        for (auto i = 0; i < secret_.size(); i++) {
            if (guessStr[i] == secret_[i])
                size++;
        }

        times_++;
        return size;
    }

};



class FindSecretWord {

	int match(const string& a, const string& b) {
		int size = 0;
		for (auto i = 0; i < a.size(); i++)
			if (a[i] != b[i])
				size++;

		return size;
	}

public:

	// incorrect
    void doit1(vector<string>& wordlist, Master& master) {
        
        int n = 0;
		int size = wordlist.size();
        vector<pair<string, int>> check;
        
        while (n < 6) {

			int randNum = rand() % size;
			bool target = true;

			for (auto& a : check) {
				if (match(wordlist[randNum], a.first) != a.second)
					target = false;
			}

			if (target)
				check.push_back({ wordlist[randNum], master.guess(wordlist[randNum]) });

			if (check.back().second == 6)
				break;
        }

    }
	
	void doit(vector<string>& wordlist, Master& master) {
		for (int i = 0, x = 0; i < 10 && x < 6; ++i) {
			// get the most-simliar one to the rest (by minimized val)
			unordered_map<string, int> count;
			for (string w1 : wordlist) 
				for (string w2 : wordlist) 
					if (match(w1, w2) == 0) 
						count[w1]++;
			
			pair<string, int> minimax = make_pair(wordlist[0], 1000);
			for (string w : wordlist)
				if (count[w] <= minimax.second) 
					minimax = make_pair(w, count[w]);
			
			x = master.guess(minimax.first);

			vector<string> wordlist2;
			for (string w : wordlist) 
				if (match(minimax.first, w) == x) 
					wordlist2.push_back(w);
			
			wordlist = wordlist2;
		}
	}

	// incorrect
	void doit2(vector<string>& wordlist, Master& master) {

		int n = 0, times = 0;
			
		while (times < 10 && n < 6) {
			int num = rand() % wordlist.size();

			int idx = master.guess(wordlist[num]);

			vector<string> newLwordlist;
			for (auto& c : wordlist) {
				if (match(c, wordlist[num]) == idx) {
					newLwordlist.push_back(c);
				}
			}
			times++;
			n = idx;
			wordlist.swap(newLwordlist);
		}
	}
    
};

void Test_843_GuesstheWorld() {

    FindSecretWord().doit(vector<string>{"acckzz","ccbazz","eiowzz","abcczz"}, Master("acckzz"));    

	return;
}
