import heapq
import itertools

# A priority queue is common use for a heap, and it presents several implementation challenges:

# Sort stability: how do you get two tasks with equal priorities to be returned in the order they were originally added?
# In the future with Python 3, tuple comparison breaks for (priority, task) pairs if the priorities are equal and the tasks do not have a default comparison order.
# If the priority of a task changes, how do you move it to a new position in the heap?
# Or if a pending task needs to be deleted, how do you find it and remove it from the queue?
# A solution to the first two challenges is to store entries as 3-element list including the priority, an entry count, and the task. The entry count serves as a tie-breaker so that two tasks with the same priority are returned in the order they were added. And since no two entry counts are the same, the tuple comparison will never attempt to directly compare two tasks.

# The remaining challenges revolve around finding a pending task and making changes to its priority or removing it entirely. Finding a task can be done with a dictionary pointing to an entry in the queue.

# Removing the entry or changing its priority is more difficult because it would break the heap structure invariants. So, a possible solution is to mark the existing entry as removed and add a new entry with the revised priority:


class PriorityQueue:
    

    def __init__(self):

        self.__entry = {}
        self.__pq = []
        self.__cnt = itertools.count()
        

    def add_task(self, task, priority):

        if task in self.__entry:
            self.remove_task(task)

        entry = [priority, next(self.__cnt), task]
        self.__entry[task] = entry
        heapq.heappush(self.__pq, entry)

    def remove_task(task):
        entry = self.__entry[task]
        entry[-1] = "REMOVED"

    def pop_task():
        while self.__pq:

            priority, cnt, task = heapq.heappop(self.__pq)
            if task is not "REMOVED":
                del self.__entry[task]
                return task
        else:
            raise KeyError('pop from an empty priority queue')
        


    
    