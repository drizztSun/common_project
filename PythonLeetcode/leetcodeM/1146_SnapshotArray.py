# 1146. Snapshot Array

# Implement a SnapshotArray that supports the following interface:

# SnapshotArray(int length) initializes an array-like data structure with the given length.  Initially, each element equals 0.
# void set(index, val) sets the element at the given index to be equal to val.
# int snap() takes a snapshot of the array and returns the snap_id: the total number of times we called snap() minus 1.
# int get(index, snap_id) returns the value at the given index, at the time we took the snapshot with the given snap_id


# Example 1:

# Input: ["SnapshotArray","set","snap","set","get"]
# [[3],[0,5],[],[0,6],[0,0]]
# Output: [null,null,0,null,5]
# Explanation:
# SnapshotArray snapshotArr = new SnapshotArray(3); // set the length to be 3
# snapshotArr.set(0,5);  // Set array[0] = 5
# snapshotArr.snap();  // Take a snapshot, return snap_id = 0
# snapshotArr.set(0,6);
# snapshotArr.get(0,0);  // Get the value of array[0] with snap_id = 0, return 5


# Constraints:

# 1 <= length <= 50000
# At most 50000 calls will be made to set, snap, and get.
# 0 <= index < length
# 0 <= snap_id < (the total number of times we call snap())
# 0 <= val <= 10^9


class SnapshotArray:

    def __init__(self, length: int):
        self._snapid = 0
        self._buff = [[[0, 0]] for _ in range(length)]

    def set(self, index: int, val: int) -> None:
        if index < len(self._buff):
            if self._snapid == self._buff[index][-1][0]:
                self._buff[index][-1][1] = val
            else:
                self._buff[index].append([self._snapid, val])
                    
    def snap(self) -> int:
        self._snapid += 1
        return self._snapid - 1

    def get(self, index: int, snap_id: int) -> int:
        from bisect import bisect_left
        snap_id += 1
        
        id = bisect_left(self._buff[index], [snap_id, 0])
        
        if id == len(self._buff[index]) or self._buff[index][id][0] > snap_id:
            id -= 1
            
        return self._buff[index][id][1]
        
class SnapshotArray:

    def __init__(self, length: int):
        self.current_snapid = 0
        self.snaparr={}


    def set(self, index: int, val: int) -> None:
        if(index not in self.snaparr):
            self.snaparr[index]={}
        self.snaparr[index][self.current_snapid]=val

    def snap(self) -> int:
        self.current_snapid+=1
        return self.current_snapid-1
        

    def get(self, index: int, snap_id: int) -> int:
        if(index not in self.snaparr):  #never touched
            return 0
        snaparr_idx =  self.snaparr[index]
        while(snap_id>=0):
            if(snap_id in snaparr_idx):
                return snaparr_idx[snap_id]
            else:
                snap_id-=1   #not modified in this snap, check previous version
        return 0    #default value
        

"""
    Intuition
    Instead of copy the whole array,
    we can only record the changes of set.
    
    
    Explanation
    The idea is, the whole array can be large,
    and we may take the snap tons of times.
    (Like you may always ctrl + S twice)
    
    Instead of record the history of the whole array,
    we will record the history of each cell.
    And this is the minimum space that we need to record all information.
    
    For each A[i], we will record its history.
    With a snap_id and a its value.
    
    When we want to get the value in history, just binary search the time point.
    
    
    Complexity
    Time O(logS)
    Space O(S)
    where S is the number of set called.
    
    SnapshotArray(int length) is O(N) time
    set(int index, int val) is O(1) in Python and O(logSnap) in Java
    snap() is O(1)
    get(int index, int snap_id) is O(logSnap)
"""

class SnapshotArray:

    def __init__(self, n):
        self.A = [[[-1, 0]] for _ in range(n)]
        self.snap_id = 0

    def set(self, index, val):
        self.A[index].append([self.snap_id, val])

    def snap(self):
        self.snap_id += 1
        return self.snap_id - 1

    def get(self, index, snap_id):
        import bisect
        i = bisect.bisect(self.A[index], [snap_id + 1]) - 1
        return self.A[index][i][1]