"""
621. Task Scheduler

Given a characters array tasks, representing the tasks a CPU needs to do, where each letter represents a different task.
Tasks could be done in any order. Each task is done in one unit of time. For each unit of time, the CPU could complete either one task or just be idle.

However, there is a non-negative integer n that represents the cooldown period between two same tasks (the same letter in the array),
that is that there must be at least n units of time between any two same tasks.

Return the least number of units of times that the CPU will take to finish all the given tasks.



Example 1:

Input: tasks = ["A","A","A","B","B","B"], n = 2
Output: 8
Explanation:
A -> B -> idle -> A -> B -> idle -> A -> B
There is at least 2 units of time between any two same tasks.
Example 2:

Input: tasks = ["A","A","A","B","B","B"], n = 0
Output: 6
Explanation: On this case any permutation of size 6 would work since n = 0.
["A","A","A","B","B","B"]
["A","B","A","B","A","B"]
["B","B","B","A","A","A"]
...
And so on.
Example 3:

Input: tasks = ["A","A","A","A","A","A","B","C","D","E","F","G"], n = 2
Output: 16
Explanation:
One possible solution is
A -> B -> C -> A -> D -> E -> A -> F -> G -> A -> idle -> idle -> A -> idle -> idle -> A


Constraints:

1 <= task.length <= 10^4
tasks[i] is upper-case English letter.
The integer n is in the range [0, 100].


"""


class TaskScheduler:

    """
    Algorithm

    The maximum number of tasks is 26. Let's allocate an array frequencies of 26 elements to keep the frequency of each task.

    Iterate over the input array and store the frequency of task A at index 0, the frequency of task B at index 1, etc.

    Sort the array and retrieve the maximum frequency f_max. This frequency defines the max possible idle time: idle_time = (f_max - 1) * n.

    Pick the elements in the descending order one by one. At each step, decrease the idle time by min(f_max - 1, f)
    where f is a current frequency. Remember, that idle_time is greater or equal to 0.

    Return busy slots + idle slots: len(tasks) + idle_time.

    Complexity Analysis

    Time Complexity: O(N) is a number of tasks to execute.
    This time is needed to iterate over the input array tasks and compute the array frequencies.
      Array frequencies contains 26 elements, and hence all operations with it takes constant time.

    Space Complexity: O(1), to keep the array frequencies of 26 elements.
    """
    def doit_greedy(self, tasks: list, n: int) -> int:
        # frequencies of the tasks
        frequencies = [0] * 26
        for t in tasks:
            frequencies[ord(t) - ord('A')] += 1

        frequencies.sort()

        # max frequency
        f_max = frequencies.pop()

        # max possible idle_time
        idle_time = (f_max - 1) * n

        while frequencies and idle_time > 0:
            idle_time -= min(f_max - 1, frequencies.pop())
        idle_time = max(0, idle_time)

        return idle_time + len(tasks)

    """
    Algorithm

    The maximum number of tasks is 26. Let's allocate an array frequencies of 26 elements to keep the frequency of each task.
    
    Iterate over the input array and store the frequency of task A at index 0, the frequency of task B at index 1, etc.
    
    Find the maximum frequency: f_max = max(frequencies).
    
    Find the number of tasks which have the max frequency: n_max = frequencies.count(f_max).
    
    If the number of slots to use is defined by the most frequent task, it's equal to (f_max - 1) * (n + 1) + n_max.
    
    Otherwise, the number of slots to use is defined by the overall number of tasks: len(tasks).
    
    Return the maximum of these two: max(len(tasks), (f_max - 1) * (n + 1) + n_max).
    
    Implementation
    
    saying A is more frequent tasks
    A----A----A----A---- (n dice --)
    if there is no enough A, those tasks, B, C ... can fill those gaps. so that total time is len(tasks)
    
    if there is enough A, it means tasks can't fill all slot
    
    ABCD-ABC--AB--AB, (n + 1) is enough round time, AB is n_max
    
    if n is big enough there is cooldown idel, if n is small enough, it is each to len(tasks)
    """
    def doit_math(self, tasks: list, n: int) -> int:
        # frequencies of the tasks
        frequencies = [0] * 26
        for t in tasks:
            frequencies[ord(t) - ord('A')] += 1

        # max frequency
        f_max = max(frequencies)
        # count the most frequent tasks
        n_max = frequencies.count(f_max)

        return max(len(tasks), (f_max - 1) * (n + 1) + n_max)

    def doit_(self, tasks, n):
        """
        :type tasks: List[str]
        :type n: int
        :rtype: int
        """
        from collections import Counter
        tasks_cnt = Counter(tasks)
        index = 0

        while tasks_cnt:

            tasklist = tasks_cnt.most_common(n + 1)

            for task, cn in tasklist:

                tasks_cnt[task] -= 1
                index += 1
                if tasks_cnt[task] == 0:
                    del tasks_cnt[task]

            if tasks_cnt and len(tasklist) < n + 1:
                index += n + 1 - len(tasklist)

        return index

    def doit_(self, tasks, n):
        """
        :type tasks: List[str]
        :type n: int
        :rtype: int
        """
        tasks_cnt = {}
        max_count, max_val = 0, 0

        for c in tasks:
            tasks_cnt[c] = tasks_cnt.get(c, 0) + 1

            if tasks_cnt[c] == max_val:
                max_count += 1
            elif tasks_cnt[c] > max_val:
                max_val = tasks_cnt[c]
                max_count = 1

        avail_slots = (max_val - 1) * (n - max_count + 1)
        avail_items = len(tasks) - max_val * max_count
        idle_slot = max(0, avail_slots - avail_items)
        return len(tasks) + idle_slot


if __name__ == '__main__':

    TaskScheduler().doit_dp(tasks = ["A","A","A","B","B","B"], n = 2)

    TaskScheduler().doit_dp(tasks = ["A","A","A","B","B","B"], n = 0)

    TaskScheduler().doit_dp(tasks = ["A","A","A","A","A","A","B","C","D","E","F","G"], n = 2)
