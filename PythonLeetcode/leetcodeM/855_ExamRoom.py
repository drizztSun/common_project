# 855. Exam Room

# In an exam room, there are N seats in a single row, numbered 0, 1, 2, ..., N-1.

# When a student enters the room, they must sit in the seat that maximizes the distance to the closest person.
# If there are multiple such seats, they sit in the seat with the lowest number.
# (Also, if no one is in the room, then the student sits at seat number 0.)

# Return a class ExamRoom(int N) that exposes two functions: ExamRoom.seat() returning an int representing what seat the student sat in, and ExamRoom.
# leave(int p) representing that the student in seat number p now leaves the room.
# It is guaranteed that any calls to ExamRoom.leave(p) have a student sitting in seat p.


# Example 1:

# Input: ["ExamRoom","seat","seat","seat","seat","leave","seat"], [[10],[],[],[],[],[4],[]]
# Output: [null,0,9,4,2,null,5]
# Explanation:
# ExamRoom(10) -> null
# seat() -> 0, no one is in the room, then the student sits at seat number 0.
# seat() -> 9, the student sits at the last seat number 9.
# seat() -> 4, the student sits at the last seat number 4.
# seat() -> 2, the student sits at the last seat number 2.
# leave(4) -> null
# seat() -> 5, the student sits at the last seat number 5.
# Note:

# 1 <= N <= 10^9
# ExamRoom.seat() and ExamRoom.leave() will be called at most 10^4 times across all test cases.
# Calls to ExamRoom.leave(p) are guaranteed to have a student currently sitting in seat number p.


"""
Approach 1: Maintain Sorted Positions
Intuition

We'll maintain ExamRoom.students, a sorted list (or TreeSet in Java) of positions the students are currently seated in.

Algorithm

The ExamRoom.leave(p) operation is clear - we will just list.remove (or TreeSet.remove) the student from ExamRoom.students.

Let's focus on the ExamRoom.seat() : int operation. For each pair of adjacent students i and j,
the maximum distance to the closest student is d = (j - i) / 2, achieved in the left-most seat i + d.
Otherwise, we could also sit in the left-most seat, or the right-most seat.

Finally, we should handle the case when there are no students separately.

For more details, please review the comments made in the implementations.

Complexity Analysis

Time Complexity: Each seat operation is O(P)O(P), (where PP is the number of students sitting), as we iterate through every student.
Each leave operation is O(P)O(P) (\log PlogP in Java).

Space Complexity: O(P)O(P), the space used to store the positions of each student sitting.

"""
import bisect
import heapq


class ExamRoom(object):
    def __init__(self, N):
        self.N = N
        self.students = []

    def seat(self):
        # Let's determine student, the position of the next
        # student to sit down.
        if not self.students:
            student = 0
        else:
            # Tenatively, dist is the distance to the closest student,
            # which is achieved by sitting in the position 'student'.
            # We start by considering the left-most seat.
            dist, student = self.students[0], 0
            for i, s in enumerate(self.students):
                if i:
                    prev = self.students[i-1]
                    # For each pair of adjacent students in positions (prev, s),
                    # d is the distance to the closest student;
                    # achieved at position prev + d.
                    d = (s - prev) / 2
                    if d > dist:
                        dist, student = d, prev + d

            # Considering the right-most seat.
            d = self.N - 1 - self.students[-1]
            if d > dist:
                student = self.N - 1

        # Add the student to our sorted list of positions.
        bisect.insort(self.students, student)
        return student

    def leave(self, p):
        self.students.remove(p)


class ExamRoom1:
    def __init__(self, N: int):
        self._students = []
        self._ranges = [(-(N-1 - 0 + 1) // 2, 0, N-1)]
        self.N = N

    def seat(self):
        _, s, e = heapq.heappop(self._ranges)

        if s == 0:
            heapq.heappush(self._ranges, (-e // 2, s+1, e))
            return 0
        elif e == self.N-1:
            heapq.heappush(self._ranges, (-(self.N-2 - s + 1) // 2, s, self.N-2))
            return self.N - 1
        else:
            index = (e - s + 1) // 2
            if index != s:
                heapq.heappush(self._ranges, (-(index - s + 1) // 2, s, index - 1))
            if index != e:
                heapq.heappush(self._ranges, (-(e - index + 1) // 2, index + 1, e))
            return index

    def leave(self, p):
        left, right = p, p
        replic_heap = []
        for d, s, e in self._ranges:
            if s == p + 1:
                right = e
            if e == p - 1:
                left = e
            else:
                heapq.heappush(replic_heap, (d, s, e))

        heapq.heappush(replic_heap, (left - right - 1, left, right))
        self._students = replic_heap


class ExamRoom2:

    # 每次坐在一个使得第一个满足间距最大的位置
    # 注意两侧的间距相当于无穷即可
    #
    # 返回下一个应该坐在哪，然后考虑将其填入，再直接leave即可
    # 每次当有人离开，则从其开始向两侧，更新其与人的距离即可

    # 每次O(N)的操作，结果是TLE了
    #    def __init__(self, N: int):
    #        self.lefts=[float("inf")]*N         #i距离左侧的
    #        self.rights=[float("inf")]*N            #距离右侧的距离
    #        self.maxd=float("inf")
    #        self.n=N
    #        self.list=[True]*N
    #    def seat(self) -> int:
    #        #print(self.list,self.maxd)
    #        for i in range(self.n):
    #            if self.list[i] and min(self.lefts[i],self.rights[i])==self.maxd:
    #                break
    #        self.list[i]=False      #将其处理掉，考虑两侧的结果，处理self.maxd
    #        self.rights[i]=0
    #        self.lefts[i]=0
    #        for k in range(i-1,-1,-1):
    #            if self.list[k]:
    #                self.rights[k]=self.rights[k+1]+1
    #            else:
    #                break
    #        for k in range(i+1,self.n):
    #            if self.list[k]:
    #                self.lefts[k]=self.lefts[k-1]+1
    #            else:
    #                break
    #        self.maxd=max(min(self.lefts[j],self.rights[j])for j in range(self.n))
    #        return i
    #
    #    def leave(self, p: int) -> None:
    #        #当该人离开，则需要重新处理一遍
    #        #考虑从p的两侧开始处理，先找到p的左侧第一个False
    #        #print(self.list,self.maxd)
    #        self.list[p]=True
    #        for k1 in range(p-1,-1,-1):
    #            if not self.list[k1]:
    #                break
    #        else:
    #            self.lefts[0]=float("inf")
    #            k1=0
    #
    #        for k2 in range(p+1,self.n):
    #            if not self.list[k2]:
    #                break
    #        else:
    #            self.rights[-1]=float("inf")
    #            k2=self.n-1
    #        #考虑其结果，需要处理k1,k2之间的结果
    #        #print(k1,k2)
    #        for k in range(k1+1,k2+1):
    #            self.lefts[k]=self.lefts[k-1]+1
    #                     #表示k1为0，此时从左侧看
    #        if not self.list[k2]:
    #            self.lefts[k2]=0
    #        for k in range(k2-1,k1-1,-1):
    #            self.rights[k]=self.rights[k+1]+1
    #        if not self.list[k1]:
    #            self.rights[k1]=0
    #        self.maxd=max(min(self.lefts[j],self.rights[j])for j in range(self.n))
    #        #print(self.list,self.maxd,self.lefts,self.rights)

        # 考虑更好的方案，是直接生成么？
        # 观察TLE的结果，是考虑有很大的N的情况，此时将导致整个结果均很大
        # 如果考虑其位置结果是有规律的
        # 如果一个人离开，那么这个人所在的位置，一定是满足当前maxd的要求的结果
        # 那么可以将这个结果放入备选中
        # 实际上就是考虑，按照左侧，右侧，然后中间的方式生成，然后找到其所有值
        # 每次考虑两侧的结果即可，即slef.i, slef.j是可行的，那么就选择其中间距最大的那个来处理
        # 如果其从-1开始的，则其最大间距将取为

    #    def __init__(self, N: int):
    #        self.heap=[(-N+1,0,N-1)]
    #        self.n=N
    #    def seat(self) -> int:
    #        #print(self.heap)
    #        #if not self.heap:
    #        #    self.heap.append((-(self.n-1),1,self.n-1))
    #        #    return 0
    #        #如果一个是从0开始的，则maxd，将是i-1，而其他的，其最大间距只能是 (i+j)//2 - (i)
    #        diff,i,j=heapq.heappop(self.heap)
    #        if i==0 and j==self.n-1:        #如果是第一个
    #            heapq.heappush(self.heap,(-(self.n-2),1,self.n-1))
    #            return 0
    #        elif i==0:
    #            heapq.heappush(self.heap,(-((j+1)//2),1,j))
    #            return 0
    #        elif j==self.n-1:     #如果是最后一个，
    #            heapq.heappush(self.heap,(-((j-i+1)//2),i,self.n-2))
    #            return self.n-1
    #        else:
    #            mid=(i+j)//2
    #            if mid>i:
    #                heapq.heappush(self.heap,(-((mid-i+1)//2),i,mid-1))
    #            if j>mid:
    #                heapq.heappush(self.heap,(-((j-mid+1)//2),mid+1,j))
    #            return mid
    #    def leave(self, p: int) -> None:
    #        #每次离开的时候，相当于将其所属的两个结果拼起来
    #        #考虑直接处理一次
    #        #print(self.heap)，如果没有可用的解的时候
    #        #if not self.heap
    #        newheap=[]
    #        left=p
    #        right=p      #如果为None则说明其前面的部分是直接从p开始的
    #        for d,i,j in self.heap:
    #            if i==p+1:
    #                right=j
    #            elif j==p-1:
    #                left=i
    #            else:
    #                newheap.append((d,i,j))
    #        if left==0:        #考虑为第一个
    #            newheap.append((-(right+1),0,right))
    #        elif right==self.n-1:
    #            newheap.append((-(p-left+1),left,p))
    #        else:
    #            newheap.append((-((right-left+2)//2),left,right))
    #        heapq.heapify(newheap)
    #        self.heap=newheap

        # 重写一遍，整理思路，仍然是通过heap完成
    def __init__(self, N: int):
        self.heap = [(-N, 0, N-1)]  # 两端的结果，其距离为N-1-0+1
        self.n = N

    def seat(self):
        # print(self.heap)
        d, i, j = heapq.heappop(self.heap)
        if i == 0 and j == self.n-1:
            heapq.heappush(self.heap, (-j, 1, j))  # 因为是一端的所以是j-1+1
            return 0
        elif i == 0:
            heapq.heappush(self.heap, (-((j+1)//2), 1, j))
            return 0
        elif j == self.n-1:
            heapq.heappush(self.heap, (-((j-i+2)//2), i, self.n-2))
            return j
        else:
            mid = (i+j)//2
            if mid > i:
                heapq.heappush(self.heap, (-((mid-i+1)//2), i, mid-1))
            if j > mid:
                heapq.heappush(self.heap, (-((j-mid+1)//2), mid+1, j))
            return mid

    def leave(self, p):
        # print(self.heap)
        left, right = p, p
        newheap = []
        for d, i, j in self.heap:
            if i == p+1:
                right = j
            elif j == p-1:
                left = i
            else:
                newheap.append((d, i, j))
        if left == 0:  # 从0开始的
            newheap.append((-(right+1), 0, right))
        elif right == self.n-1:
            newheap.append((-(right-left+1), left, right))
        else:
            newheap.append(((-(right-left+2)//2), left, right))
        heapq.heapify(newheap)
        self.heap = newheap
        if not self.heap:
            self.heap = [(-self.n, 0, self.n-1)]
        # print(p,self.heap)


if __name__ == '__main__':

    # Your ExamRoom object will be instantiated and called as such:
    obj = ExamRoom1(10)
    res = obj.seat()
    res = obj.seat()
    res = obj.seat()
    res = obj.seat()
    res = obj.leave()
    res = obj.seat()
    obj.leave(p)
