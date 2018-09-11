# 621. Task Scheduler

# Given a char array representing tasks CPU need to do. 
# It contains capital letters A to Z where different letters represent different tasks.
# Tasks could be done without original order. Each task could be done in one interval. 
# For each interval, CPU could finish one task or just be idle.

# However, there is a non-negative cooling interval n that means between two same tasks, 
# there must be at least n intervals that CPU are doing different tasks or just be idle.

# You need to return the least number of intervals the CPU will take to finish all the given tasks.

# Example 1:
# Input: tasks = ["A","A","A","B","B","B"], n = 2
# Output: 8
# Explanation: A -> B -> idle -> A -> B -> idle -> A -> B.
# Note:
# The number of tasks is in the range [1, 10000].
# The integer n is in the range [0, 100].


class LeastInterval:

    def doit(self, tasks, n):
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

    def doit1(self, tasks, n):
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


    def doit2(self, tasks, n):
        """
        :type tasks: List[str]
        :type n: int
        :rtype: int
        """
        time, most_common = 0, 0
        count = collections.Counter(tasks)
        max_count = count.most_common(1)[0][1]

        for item in count:
            if count[item] == max_count:
                most_common += 1
                
        avail_slots = (max_count - 1) * (n - most_common + 1)
        avail_items = len(tasks) - most_common * max_count
        idle_slots = max(0, avail_slots - avail_items)
        time = len(tasks) + idle_slots
        
        return time

                       
if __name__ == "__main__":

    res = LeastInterval().doit(tasks = ["A","A","A","B","B","B"], n = 2)                      

    res = LeastInterval().doit(tasks = ["A","A","B","B","B"], n = 2)

