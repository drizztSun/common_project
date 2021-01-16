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
        

if __name__ == "__main__":
    """
    obj = SnapshotArray(3)
    obj.set(0, 5)
    obj.snap()
    obj.set(0, 6)
    obj.get(0, 0)
    """
    obj = SnapshotArray(4)
    obj.snap()
    obj.snap()
    obj.get(3, 1)
    obj.set(2, 4)
    obj.snap()
    obj.set(1, 4)
