/*
1093. Statistics from a Large Sample

You are given a large sample of integers in the range [0, 255]. Since the sample is so large, it is represented by an array count where count[k] is the number of times that k appears in the sample.

Calculate the following statistics:

minimum: The minimum element in the sample.
maximum: The maximum element in the sample.
mean: The average of the sample, calculated as the total sum of all elements divided by the total number of elements.
median:
        If the sample has an odd number of elements, then the median is the middle element once the sample is sorted.
        If the sample has an even number of elements, then the median is the average of the two middle elements once the sample is sorted.

mode: The number that appears the most in the sample. It is guaranteed to be unique.

Return the statistics of the sample as an array of floating-point numbers [minimum, maximum, mean, median, mode]. Answers within 10-5 of the actual answer will be accepted.

 

Example 1:

Input: count = [0,1,3,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
Output: [1.00000,3.00000,2.37500,2.50000,3.00000]
Explanation: The sample represented by count is [1,2,2,2,3,3,3,3].
The minimum and maximum are 1 and 3 respectively.
The mean is (1+2+2+2+3+3+3+3) / 8 = 19 / 8 = 2.375.
Since the size of the sample is even, the median is the average of the two middle elements 2 and 3, which is 2.5.
The mode is 3 as it appears the most in the sample.
Example 2:

Input: count = [0,4,3,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
Output: [1.00000,4.00000,2.18182,2.00000,1.00000]
Explanation: The sample represented by count is [1,1,1,1,2,2,2,3,3,4,4].
The minimum and maximum are 1 and 4 respectively.
The mean is (1+1+1+1+2+2+2+3+3+4+4) / 11 = 24 / 11 = 2.18181818... (for display purposes, the output shows the rounded number 2.18182).
Since the size of the sample is odd, the median is the middle element 2.
The mode is 1 as it appears the most in the sample.
 

Constraints:

count.length == 256
0 <= count[i] <= 109
1 <= sum(count) <= 109
The mode of the sample that count represents is unique.

*/

#include <vector>
#include <algorithm>
#include <numeric>

using std::vector;


class SampleStats {

public:

    vector<double> doit_(vector<int>& count) {
        
        int n = count.size();
        int cnts = accumulate(begin(count), end(count), 0);
        
        int l = (cnts+1) / 2, r = l + (cnts % 2 == 0);
        int max_num = 0, min_num = n;
        double median = 0, mean = 0, frequency = 0, freqnum = 0;
        
        for (int i = 0, cnt = 0; i < count.size(); cnt += count[i++]) {
            
            max_num = std::max(max_num, count[i] > 0 ? i : 0);
            min_num = std::min(min_num, count[i] > 0 ? i : n);
            
            if (cnt < l && cnt+count[i] >= l) median += double(i)/2;
            if (cnt < r && cnt+count[i] >= r) median += double(i)/2;
            
            mean += static_cast<double>(i) * count[i] / cnts;
            
            if (frequency < count[i])
                frequency = count[i], freqnum = i;
        }
        
        return {static_cast<double>(min_num), static_cast<double>(max_num), mean, median, freqnum};
    }


    /*
        This is my least favorite type of a problem - pretty straightforward, but takes a lot of time to write correctly during the contest.
        ...unless you know Python...

        First, figure out how many total elements we have (t_cnt). Then, we can determine the position of our median (m1 and m2, m1 == m2 if we have odd number of elements).

        Then, we can go through the array one more time and determine all statistics.
    */
    vector<double> doit_(vector<int>& cnts) {
        
        vector<double> res = { 255, 0, 0, 0, 0 };
        int t_cnt = std::accumulate(begin(cnts), end(cnts), 0), m_cnt = 0;
        int m1 = (t_cnt + 1) / 2, m2 = m1 + (t_cnt % 2 == 0 ? 1 : 0);

        for (auto i = 0, cnt = 0; i < cnts.size(); cnt += cnts[i++]) {
            res[0] = cnts[i] ? std::min((int)res[0], i) : res[0];
            res[1] = cnts[i] ? i : res[1];
            res[2] += (double)i * cnts[i] / t_cnt;
            
            if (cnt < m1 && cnt + cnts[i] >= m1) res[3] += (double)i / 2;
            if (cnt < m2 && cnt + cnts[i] >= m2) res[3] += (double)i / 2;
            
            res[4] = m_cnt < cnts[i] ? i : res[4];
            m_cnt = std::max(m_cnt, cnts[i]);
        }
        return res;
    }
};