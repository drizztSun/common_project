/*
1705. Maximum Number of Eaten Apples


There is a special kind of apple tree that grows apples every day for n days. On the ith day, the tree grows apples[i] apples that will rot after days[i] days, 
that is on day i + days[i] the apples will be rotten and cannot be eaten. On some days, the apple tree does not grow any apples, which are denoted by apples[i] == 0 and days[i] == 0.

You decided to eat at most one apple a day (to keep the doctors away). Note that you can keep eating after the first n days.

Given two integer arrays days and apples of length n, return the maximum number of apples you can eat.

 

Example 1:

Input: apples = [1,2,3,5,2], days = [3,2,1,4,2]
Output: 7
Explanation: You can eat 7 apples:
- On the first day, you eat an apple that grew on the first day.
- On the second day, you eat an apple that grew on the second day.
- On the third day, you eat an apple that grew on the second day. After this day, the apples that grew on the third day rot.
- On the fourth to the seventh days, you eat apples that grew on the fourth day.
Example 2:

Input: apples = [3,0,0,0,0,2], days = [3,0,0,0,0,2]
Output: 5
Explanation: You can eat 5 apples:
- On the first to the third day you eat apples that grew on the first day.
- Do nothing on the fouth and fifth days.
- On the sixth and seventh days you eat apples that grew on the sixth day.
 

Constraints:

apples.length == n
days.length == n
1 <= n <= 2 * 104
0 <= apples[i], days[i] <= 2 * 104
days[i] = 0 if and only if apples[i] = 0.

*/
#include <vector>
#include <queue>
#include <unordered_map>
#include <map>
#include <algorithm>

using std::map;
using std::unordered_map;
using std::vector;
using std::priority_queue;


class EatenApples {

    using PII = std::pair<int,int>;

    /*
        1705.Maximum-Number-of-Eaten-Apples
        本题事实上没有“高级的”贪心法。所有o(N)时间的算法都是不正确。

        比较暴力的贪心其实很容易想到：优先吃离腐败日期最近的苹果，先解决燃眉之急。数据结构选用优先队列或者其他heap。我们每一天的流程是这样的：

        1. 如果队列里有今天过期的苹果，扔掉。
        2. 如果今天有新长出来的苹果，加入队列。
        3. 取队列最上方的一批苹果，吃掉其中的一个；剩下的再放回队列。
        
        时间复杂度是o(NlogN)，其中N是天数。最多我们会遍历多少天呢？极限情况是：最后一天遇上了保质期最长的苹果，N最大是2e4+2e4.所以o(NlogN)是可以接受的。    
    */
    int doit_dp(vector<int>& apples, vector<int>& days) 
    {
        int count = 0, i = 0;
        priority_queue<PII, vector<PII>, std::greater<PII>> pq;

        while (i < apples.size() || !pq.empty()){

            while (!pq.empty() && pq.top().first <= i)
                pq.pop();
            
            if (i < apples.size() && apples[i] > 0)
                pq.push({i+days[i], apples[i]});

            if (!pq.empty()){
                
                auto x = pq.top();
                pq.pop();
                count++;

                if (x.second >= 2)
                    pq.push({x.first, x.second-1});
            }
            i++;
        }

        return count;
    }

public:

    /*
    Approach 1: Using Unordered Map And Priority Queue
    Intuition

    We aim to eat the maximum number of apples. To do that, we must eat apples that are going to rot soon. Every day, we must find apples that are going to rot first and eat one of those apples. It must be noted that we can eat only one apple per day.

    For every day given by currentDay, we have to perform 2 operations,

    Operation 1: Get new apples, apples[currentDay] that will rot after days[currentDay] days. For this, we could maintain a list of apples with information about their expiry given by applesExpiry.We must update this list every day as new apples are added.

    Operation 2: Eat one apple on currentDay. This is a little tricky. To eat an apple that will rot first, we must pick an apple from the list that will expire first after the currentDay.

    We don't care about apples that have rot before currentDay.

    The following figure illustrates the idea for apples = [3, 2] and days = [2, 4].

    img

    Let's understand how can we implement the above idea.

    Algorithm

    As mentioned above, we must maintain a list of apples that would expire on a particular day given by applesExpiry. Here, we need information on 2 parameters, the expiry day and the number of apples expiring on that day.

    The list would be updated whenever new apples are added. Also as an apple is eaten, it would be removed from the list. Thus, we need some kind of data structure where elements can be added and updated in constant time. The data structure that comes to our mind is an unordered map. We could build a map where the key would be the expiry day and values would be the number of apples expiring on that day.

    Now, that we have a list of apples expiring on a particular day (Operation 1), we must pick an apple to be eaten for each day (Operation 2).

    We have an unordered map,applesExpiry having expiry days of all apples. We can find the first expiry day after currentDay and eat one apple from that day. For this, we would have to search the entire map to find the best candidate. Can we do it in a better way?

    If we could maintain expiry days after the current day in ascending order in some kind of data structure, we could get the next expiry day in constant time. One way to implement this is by using a min-heap i.e priority queue.

    The priority queue would hold all the expiry days sorted in order of priority. In our case, the apples that would expire first would have higher priority. The top element in the queue would be the first expiry day after the current day given by latestExpiryDay. We could find the number of apples expiring on latestExpiryDay from the map applesExpiry and eat one apple i.e remove one apple.

    Maintain the number of apples eaten in variable count and increment by 11 whenever an apple is eaten.

    The above steps would continue iteratively until we have reached n days or the priority queue is empty. Return the total apples eaten given by count.

    It must be noted that, in each iteration, we must remove elements i.e expiry days from the priority queue that have passed the current day. In other words, the elements in the priority queue with a value lesser than or equal to the currentDay must be removed.

    Implementation


    Complexity Analysis

    Time Complexity : \mathcal{O}(\text{maxExpiryDay} \log (\text{maxExpiryDay}))O(maxExpiryDaylog(maxExpiryDay)), where \text{maxExpiryDay}maxExpiryDay is the maximum value among all expiry days.

    The iteration does not stop once we reach n days but it continues until the queue is empty. The maximum value in the queue would be the farthest expiry day i.e the expiry day with maximum value. Thus, the \text{maxExpiryDay}maxExpiryDay would be equal to max(currentExpiry). The time taken to complete all iterations would be \mathcal{O}({\text{maxExpiryDay}})O(maxExpiryDay).

    In each iteration we perform queue push and pop operations. As maximum size of queue could be \text{maxExpiryDay}maxExpiryDay, the push and pop operations would take \mathcal{O}(\log{\text{(maxExpiryDay)}})O(log(maxExpiryDay)) time.

    Also, in each iteration, we add and remove elements in an unordered map which takes constant time.

    This would give total time complexity as \mathcal{O}(\text{maxExpiryDay} \log (\text{maxExpiryDay}))O(maxExpiryDaylog(maxExpiryDay)).

    Space Complexity: \mathcal{O}(n)O(n), as we build the queue and map, in the worst case the maximum elements in these lists would be n.

    */

    struct Comparator {
        bool operator()(int const& p1, int const& p2) { return p1 > p2; }
    };

    int doit_heap(vector<int>& apples, vector<int>& days) {

        unordered_map<int, int> applesExpiry;
        priority_queue<int, vector<int>, Comparator> queue;

        int count = 0;
        for (int currentDay = 0; (currentDay < apples.size() || !queue.empty()); currentDay++) {
            // calculate the expiry of apples received on currentDay and update map and queue
            if (currentDay < apples.size()) {
                int currentExpiry = currentDay + days[currentDay];
                if (applesExpiry.find(currentExpiry) == applesExpiry.end()) {
                    queue.push(currentExpiry);
                }
                applesExpiry[currentExpiry] += apples[currentDay];
            }
            // remove from queue until if the expiry days have passed current day
            while (!queue.empty() && queue.top() <= currentDay) {
                queue.pop();
            }
            if (!queue.empty()) {
                // eat an apple on current day
                int latestExpiryDay = queue.top();
                count++;
                applesExpiry[latestExpiryDay] = applesExpiry[latestExpiryDay] - 1;

                if (applesExpiry[latestExpiryDay] == 0) {
                    queue.pop();
                    applesExpiry.erase(latestExpiryDay);
                }
            }
        }
        return count;
    }

    /*
        Approach 2: Using Ordered Map
        In the Approach 1, we used an unordered map to store the mapping of expiry days and number of apples. A priority queue was used to fetch the higher priority apples that will expire first and hence must be eaten first.

        However, if we use an ordered map wherein the keys i.e expiry days are sorted in increasing order, we could use the same map to fetch the apples in order of priority. Here, the ordered map sorts the keys in the map in increasing order and thus can be used to fetch the apples that would rot first.

        We must fetch the apples expiring after the currentDay, hence we would find the element in the map having the next higher key after currentDay. For example, if currentDay is 66, we would eat apples that with expire after day 66.

        Algorithm

        Build an ordered map map that would store the apple expiry information with key as the expiry day and value as the number of apples expiring on that day.

        For each day, update the map if new apples are added with their expiry information.

        Now, find the latest expiry day from the map after the currentDay given by latestExpiryDay. This can be done by using built-in functions to get the next element in map with key greater than currentDay. Get all apples expiring on latestExpiryDay and eat one apple by removing it from the map.

        Maintain the number of apples eaten in variable count and increment by 11 when an apple is eaten.

        The process would continue iteratively until we have reached n days or the map is not empty.

        Complexity Analysis

        Time Complexity : O(maxExpiryDaylog(maxExpiryDay)), where maxExpiryDay is the maximum value among all expiry days.

        The iteration does not stop once we reach n days but it continues until there is no next greater expiry day after the current day i.e we have reached the farthest expiry day with maximum value. Thus, the \text{maxExpiryDay}maxExpiryDay would be equal to max(currentExpiry). The time taken to complete all iterations would be \mathcal{O}({\text{maxExpiryDay}})O(maxExpiryDay).

        In each iteration we add and remove elements in an ordered map which takes O(log(maxExpiryDay)) time. Getting next higher key after current day also takes \mathcal{O}( \log (\text{maxExpiryDay}))O(log(maxExpiryDay)) time.

        This would give total time complexity as O(maxExpiryDaylog(maxExpiryDay)).

        Space Complexity: \mathcal{O}(n)O(n), as we build the the map, in the worst case the maximum elements in the map would be n.

    */
    int doit_heap(vector<int>& apples, vector<int>& days) {
        map<int, int> map;
        int count = 0;
        for (int currentDay = 0; currentDay < apples.size() || map.upper_bound(currentDay) != map.end(); currentDay++) {
            // calculate the expiry of apples received on currentDay and update
            // map
            if (currentDay < apples.size()) {
                int currentExpiry = currentDay + days[currentDay];
                map[currentExpiry] += apples[currentDay];
            }
            // eat an apple on current day
            auto latestExpiryDay = map.upper_bound(currentDay);
            if (latestExpiryDay != map.end()) {
                count++;
                if (map[latestExpiryDay->first] > 1)
                    map[latestExpiryDay->first]--;
                else
                    map.erase(latestExpiryDay);
            }
        }
        return count;
    }
    /*
        Approach 3: Using Ordered Map Optimized Approach
        Intuition

        In the previous approach, we used an ordered map to fetch the apples that would rot first instead of using an additional priority queue. This was implemented by getting the next higher value after current day which takes \mathcal{O}( \log (\text{maxExpiryDay}))O(log(maxExpiryDay)) time. Can we achieve this in constant time, as we did using a priority queue?

        We must ensure that the top element in an ordered map is the latest expiry day of apples. This latest expiry day must be after the current day. The apples that expired before the current day are already rotten. We must remove those from the map, as we removed them from the queue in Approach 1.

        Algorithm

        Build an ordered map map that would store the apple expiry information with key as the expiry day and value as the number of apples expiring on that day.

        For each day, update the map if new apples are added with their expiry information.

        We must remove the expiry days from the map that have already passed the current day. For this, we must remove the elements from the top of map until it's key is less than or equal to currentDay.

        Now, the top element of the map is the latest expiry day given by latestExpiryDay after the currentDay. Get all apples expiring on latestExpiryDay and eat one apple by removing it from the map.

        Maintain the number of apples eaten in variable count and increment by 11 when every apple is eaten.

        The process would continue iteratively until we have reached n days or the map is not empty.

        The ordered map can be implemented using TreeMap in Java and map in C++.

        Implementation


        Complexity Analysis

        Time Complexity : \mathcal{O}(\text{maxExpiryDay} \log (\text{maxExpiryDay}))O(maxExpiryDaylog(maxExpiryDay)), where \text{maxExpiryDay}maxExpiryDay is the maximum value among all expiry days.

        The iteration does not stop once we reach n days but it continues until the map is empty. The maximum value in the map would be the farthest expiry day i.e the expiry day with maximum value. Thus, the \text{maxExpiryDay}maxExpiryDay would be equal to max(currentExpiry). The time taken to complete all iterations would be \mathcal{O}({\text{maxExpiryDay}})O(maxExpiryDay).

        In each iteration we add and remove elements from map. As maximum size of map could be \text{maxExpiryDay}maxExpiryDay, the add and remove operations would take \mathcal{O}(\log{\text{(maxExpiryDay)}})O(log(maxExpiryDay)) time.

        This would give total time complexity as \mathcal{O}(\text{maxExpiryDay} \log (\text{maxExpiryDay}))O(maxExpiryDaylog(maxExpiryDay)).

        Space Complexity: \mathcal{O}(n)O(n), as we build the the map, in the worst case the maximum elements in the map would be n.
    */
    int doit_heap(vector<int>& apples, vector<int>& days) {
        map<int, int> applesExpiry;
        int count = 0;
        for (int currentDay = 0;
             currentDay < apples.size() || !applesExpiry.empty();
             currentDay++) {
            // calculate the expiry of apples received on currentDay and update map
            if (currentDay < apples.size()) {
                int currentExpiry = currentDay + days[currentDay];
                applesExpiry[currentExpiry] =
                    applesExpiry[currentExpiry] + apples[currentDay];
            }
            // remove from map until if the expiry days have passed current day
            while (!applesExpiry.empty() &&
                   applesExpiry.begin()->first <= currentDay) {
                applesExpiry.erase(applesExpiry.begin()->first);
            }
            // eat an apple on current day
            if (!applesExpiry.empty()) {
                int latestExpiryDay = applesExpiry.begin()->first;
                count++;
                if (applesExpiry[latestExpiryDay] > 1)
                    applesExpiry[latestExpiryDay] =
                        applesExpiry[latestExpiryDay]--;
                else
                    applesExpiry.erase(latestExpiryDay);
            }
        }
        return count;
    }

    /*
        Approach 4 : Using Array
        Intuition

        This is just another way of implementing an ordered map that is sorted by expiry days in increasing order. An array can also be used as a map. We know that the array stores contiguous elements, hence the array indexes can be the expiry days and its value would be the number of apples expiring on that day.

        For example, if applesExpiry is an array that stores the apple expiry information, for a given day i, applesExpiry[i] would store the number of apples expiring on i^{th}i 
        th
        day.

        Algorithm

        The implementation of an array as a map instead of an ordered map (as in Approach 2) has certain differences,

        As we are using an array, we must fix its size. To know the size of the array we must answer this question - For any given problem, what would be the maximum number of days?

        For a problem having n days, on n^{th}n 
        th
        day, the maximum value of days[n] could be 20000 (2 * 10^{4})20000(2∗10 
        4
        ). Thus, we would build a fixed size array applesExpiry of size n + 20000n+20000.

        In the ordered map, we removed the elements where the expiry days had passed the current day. In the case of an array, we could simply increment the pointer to find the next expiry day after the current day. Let's use a pointer latestExpiryPointer for this purpose.

        The latestExpiryPointer will always point to the next expiry day after currentDay when a certain number of apples are going to expire. To ensure this condition, in every iteration, the latestExpiryPointer is incremented until latestExpiryPointer is less than or equal to currentDay or if no apples are expiring on a day.

        What should be the terminating condition? In previous approaches, we terminated when the farthest expiry day was reached and the map was empty. Here, we would have to find the maximum expiry day which would be our last day. Let the variable be lastDay and in every iteration, we would update the lastDay to be the maximum value of currentExpiry.

        The iteration would terminate when currentDay is equal to the lastDay.

        The following figure illustrates the idea for apples = [3, 2] and days = [2, 4].

        img

        Implementation


        Complexity Analysis

        Time Complexity : \mathcal{O}({\text{maxExpiryDay}})O(maxExpiryDay), where \text{maxExpiryDay}maxExpiryDay is the maximum value among all expiry days. The iteration continues until currentDay is equal to lastDay. The value of lastDay is equal to maximum of all expiry days, given by max(currentExpiry).

        Space Complexity: \mathcal{O}(n)O(n), as we an array of size n + 20001n+20001, the space complexity would be roughly equal to \mathcal{O}(n)O(n).

    */
    int doit_array(vector<int>& apples, vector<int>& days) {

        int n = apples.size();
        vector<int> applesExpiry(n + 20001, 0);
        int count = 0;
        int lastDay = n;
        int latestExpiryPointer = 0;

        for (int currentDay = 0; currentDay < lastDay; currentDay++) {
            
            // calculate the expiry of apples received on currentDay and update
            // map
            if (currentDay < n) {
                int currentExpiry = days[currentDay] + currentDay;
                applesExpiry[currentExpiry] += apples[currentDay];
                if (currentExpiry < latestExpiryPointer)
                    latestExpiryPointer = currentExpiry;
                // update last day if current expiry is greater
                if (currentExpiry > lastDay) lastDay = currentExpiry;
            }
            
            while ((latestExpiryPointer <= currentDay ||
                    applesExpiry[latestExpiryPointer] == 0) &&
                   latestExpiryPointer < lastDay) {
                latestExpiryPointer++;
            }

            // eat an apple on current day
            if (applesExpiry[latestExpiryPointer] != 0) {
                applesExpiry[latestExpiryPointer]--;
                count++;
            }
        }
        return count;
    }
};