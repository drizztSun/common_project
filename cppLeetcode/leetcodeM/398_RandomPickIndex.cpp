/*
398. Random Pick Index

Given an array of integers with possible duplicates, randomly output the index of a given target number. You can assume that the given target number must exist in the array.

Note:
The array size can be very large. Solution that uses too much extra space will not pass the judge.

Example:

int[] nums = new int[] {1,2,3,3,3};
Solution solution = new Solution(nums);

// pick(3) should return either index 2, 3, or 4 randomly. Each index should have equal probability of returning.
solution.pick(3);

// pick(1) should return 0. Since in the array only nums[0] is equal to 1.
solution.pick(1);
*/


/*
Approach 3: Reservoir sampling
Intuition

Reservoir sampling is a technique which is used to generate numbers randomly when we have a large pool of numbers. 
As mentioned in the note for this question, the array size can be large, hence it is a reasonable choice to use Reservoir Sampling. 
Consider an array of size nn from which we need to chose a number randomly. Consider these numbers to be coming in the form of a stream, 
hence at each step, we have to take the decision of whether or not to choose a given number, such that the overall probability of each number being chosen is same (\frac{1}{n} 
n
1
​	
  in this case). If we have a total of nn numbers and we pick the i^{th}i 
th
  number, this implies that we do not pick any number further from index (i + 1)(i+1) to nn. In terms of probability, this can be represented as

\frac{1}{i} * \frac{i}{i + 1} * \frac{i + 1}{i + 2} ... * \frac{n - 1}{n} 

This can be interpreted as

Picking the i^{th}i 
th
  number from the list of ii numbers

Not picking the (i + 1)^{th}(i+1) 
th
  number from the list of (i + 1)(i+1) numbers. Hence picking any of the remaining ii numbers.

And so on ...

Not picking the (n)^{th}(n) 
th
  number from the list of (n)(n) numbers. Hence picking any of the remaining (n - 1)(n−1) numbers.

Upon simplifying the above expression, we can see that the probability of chosing any number at the i^{th}i 
th
  step comes out to be \frac{1}{n} 
n
1
​	
 . Hence we can say that reservoir sampling allows us to choose any number uniformly at random from the list of nn numbers.

Note that for any ii, the decision of whether or not to choose this i^{th}i 
th
  number depends on the first term of the above mentioned expression, which is \frac{1}{i} 
i
1
​	
 . In general, if count represents the total number of numbers we have from which we need to chose a random number uniformly, we chose such a number with probability \frac{1}{count} 
count
1
​	
 . This is what we will be doing here.

Algorithm

Below is the implementation of the above mentioned approach.
*/

class RandomPick {
public:
    
    vector<int> nums;
    
    RandomPick(vector<int>& nums) {
        this->nums.swap(nums);
    }
    
    //O(n)
    int pick(int target) {
        int n = nums.size();
        int count = 0;
        int idx = 0;
        for (int i = 0; i < n; ++i) {
            // if nums[i] is equal to target, i is a potential candidate
            // which needs to be chosen uniformly at random
            if (nums[i] == target) {
                // increment the count of total candidates
                // available to be chosen uniformly at random
                count++;
                // we pick the current number with probability 1 / count (reservoir sampling)
                if (rand() % count == 0) {
                    idx = i;
                }
            }
        }
        return idx;
    }
};

/*

Approach 1: Brute force
Intuition

In this approach, we will simply store the indices of all the numbers equal to target that are present in the array and will return an index at random. 
The drawback of this approach is, every time the pick method is called, an extra space is required, which is dependent on the number of occurences of the number target in the given array.

Algorithm

Below is the implementation of the above mentioned approach.

Complexity Analysis

Time Complexity

pick - If N represents the size of the nums array, the time complexity of pick method is O(N).
Space Complexity: O(N) (space required by indices in pick method).

*/
#include <vector>
using std::vector;

#include <unordered_map>
using std::unordered_map;

class RandomPickArray{
private:

    vector<int> nums;

public:
    
    RandomPickArray(vector<int>& nums) {
        // Do not allocate extra space for the nums array
        this->nums.swap(nums);
    }
    
    int pick(int target) {
        vector<int> indices;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            if (nums[i] == target) {
                indices.push_back(i);
            }
        }
        int l = indices.size();
        int randomIndex = indices[rand() % l];
        return randomIndex;
    }
};


/*
Approach 2: Caching results using a hashmap
Intuition

In this approach, instead of extracting all the positions in the pick method where a given target is present, we'll pre-compute it. 
Hence for each of the number present in the array nums, we'll store all the positions (indices) where this number occurs. 
This will avoid unnecessary creation of indices array in case pick method is given a target value which is repeated. Since we are storing all the indices for each of the number, hence the space requirement for this approach is huge.

Algorithm

Below is the implementation of the above mentioned approach.

Complexity Analysis

Time Complexity

If NN represents the size of the nums array, building indices takes O(N) time.

pick method takes O(1) time.

Space Complexity: O(N) required for indices.


*/

class RandomPickHash {
private:

    unordered_map<int, vector<int>> indices;

public:
    
    RandomPickHash(vector<int>& nums) {
        int l = nums.size();
        for (int i = 0; i < l; ++i) {
            this->indices[nums[i]].push_back(i);
        }
    }
    // O(1)
    int pick(int target) {
        int l = indices[target].size();
        // pick an index at random
        int randomIndex = indices[target][rand() % l];
        return randomIndex;
    }
};