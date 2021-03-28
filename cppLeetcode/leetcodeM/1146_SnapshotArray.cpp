/*
1146. Snapshot Array

Implement a SnapshotArray that supports the following interface:

. SnapshotArray(int length) initializes an array-like data structure with the given length.  Initially, each element equals 0.
. void set(index, val) sets the element at the given index to be equal to val.
. int snap() takes a snapshot of the array and returns the snap_id: the total number of times we called snap() minus 1.
. int get(index, snap_id) returns the value at the given index, at the time we took the snapshot with the given snap_id
 

Example 1:

Input: ["SnapshotArray","set","snap","set","get"]
[[3],[0,5],[],[0,6],[0,0]]
Output: [null,null,0,null,5]
Explanation: 
SnapshotArray snapshotArr = new SnapshotArray(3); // set the length to be 3
snapshotArr.set(0,5);  // Set array[0] = 5
snapshotArr.snap();  // Take a snapshot, return snap_id = 0
snapshotArr.set(0,6);
snapshotArr.get(0,0);  // Get the value of array[0] with snap_id = 0, return 5
 

Constraints:

1 <= length <= 50000
At most 50000 calls will be made to set, snap, and get.
0 <= index < length
0 <= snap_id < (the total number of times we call snap())
0 <= val <= 10^9

*/
#include <vector>
#include <unordered_set>
#include <map>
#include <unordered_map>


using std::unordered_map;
using std::map;
using std::unordered_set;
using std::vector;

class SnapshotArray {

    int _snapid;
    vector<map<int, int>> _buf;

public:
    SnapshotArray(int length) :_buf(length), _snapid(0) {

        for (int i = 0; i < length; i++)
            _buf[i].emplace(0, 0);
    }
    
    void set(int index, int val) {

        _buf[index][_snapid] = val;
    }
    
    int snap() {
        return _snapid++;
    }
    
    int get(int index, int snap_id) {
        
        auto it = _buf[index].lower_bound(snap_id);

        if (it != _buf[index].end() && it->first == snap_id)
            return it->second;

        if (it != _buf[index].begin() && prev(it)->first < snap_id)
            return prev(it)->second; 

        return -1;
    }
};

/*
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
*/

class SnapshotArray {

    map<int, map<int, int>> snaps;
    int snapId = 0;
public:
    SnapshotArray(int length) {
        for (int i = 0; i < length; i++) {
            map<int, int> mp; mp[0] = 0;
            snaps[i] = mp;
        }
    }
    
    void set(int index, int val) {
        snaps[index][snapId] = val;
    }
    
    int snap() {
        return snapId++;
    }
    
    int get(int index, int snap_id) {
        auto it = snaps[index].upper_bound(snap_id); it--;
        return it->second;
    }
};

class SnapshotArray {
private:
    //key: index, value pair: [snapId, val]
    unordered_map<int, vector<std::pair<int, int>>> valueBySnapId;
    int snapId = 0;
public:
    SnapshotArray(int length) {
        
    }
    
    void set(int index, int val) {
        if (valueBySnapId.count(index) && valueBySnapId[index].back().first == snapId)
            valueBySnapId[index].back().second = val;
        else
            valueBySnapId[index].push_back({snapId, val});
    }
    
    int snap() {
        return snapId++;
    }
    
    int get(int index, int snap_id) {
        if (valueBySnapId.find(index) == valueBySnapId.end()) return 0;
        if (valueBySnapId[index].front().first <= snap_id){
            auto cmp = [](const int val, const std::pair<int, int>& p){
                return val < p.first;
            };
            auto it = std::upper_bound(valueBySnapId[index].begin(), valueBySnapId[index].end(), snap_id, cmp);
            --it;
            return it->second;
        }
        return 0;
    }
};


/*
1146.Snapshot-Array
最直观的想法就是给每个元素设立快照，即snaps[index]记录了关于index这个元素所有的{snapId, val}。

接下来我们需要考虑一个效率的问题。我们每调用一次snap()是否需要给每个元素都新建一次快照呢？显然如果大多数元素都没有更新过的话，再添加一次快照的效率不高。所以我们可以设置一个changed的集合，里面只存放上一次snap()之后变动过的元素，也就是被set()过的元素。

这样的话，我们会发现对于每个元素而言，它被记录的snapId并不是连续的。比如说snaps[index]={{1,4},{3,8}}，即该元素在第一次拍快照时的值是4，第三次拍快照时的值是8. 那么我们在第二次拍快照的时候，该元素的值是什么呢？显然哪个时候它的值应该是与snapId==1时的值是一样的。所以我们应该在snaps[index]里面找到最后一个小于等于snapId的那个时间戳。

此外还有一个细节，如果某个元素从来没有被更新过，那么snaps[index]里面就是空的，二分搜值就得不到结果。解决方法是，考虑到每个元素的初始值是0，我们给它虚拟地加一个快照{-1,0}，即它的snapId可以认为是-1. 这样get(index,snap_id)的时候至少能得到初始值0.
*/
class SnapshotArray {

    int vals[50000];
    vector<vector<std::pair<int,int>>> snaps;
    unordered_set<int>changed;
    int snapId;

public:
    SnapshotArray(int length) 
    {    
        snapId = 0;
        snaps.resize(length);
        for (int i=0; i<length; i++)
            snaps[i].push_back({-1,0});
    }
    
    void set(int index, int val) 
    {
        vals[index] = val;
        changed.insert(index);
    }
    
    int snap() 
    {
        for (int index: changed)
        {
            snaps[index].push_back({snapId, vals[index]});
        }
        snapId++;
        changed.clear();
        return snapId-1;
    }
    
    int get(int index, int snap_id) 
    {
        auto iter = upper_bound(snaps[index].begin(), snaps[index].end(), make_pair(snap_id, INT_MAX));
        iter = prev(iter,1);
        return iter->second;                                        
    }
};
