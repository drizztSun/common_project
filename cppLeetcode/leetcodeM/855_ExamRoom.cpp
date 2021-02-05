/*
855. Exam Room


In an exam room, there are N seats in a single row, numbered 0, 1, 2, ..., N-1.

When a student enters the room, they must sit in the seat that maximizes the distance to the closest person.  If there are multiple such seats, they sit in the seat with the lowest number.  
(Also, if no one is in the room, then the student sits at seat number 0.)

Return a class ExamRoom(int N) that exposes two functions: ExamRoom.seat() returning an int representing what seat the student sat in, and ExamRoom.leave(int p) representing that the student in seat number p now leaves the room.  
It is guaranteed that any calls to ExamRoom.leave(p) have a student sitting in seat p.

 

Example 1:

Input: ["ExamRoom","seat","seat","seat","seat","leave","seat"], [[10],[],[],[],[],[4],[]]
Output: [null,0,9,4,2,null,5]
Explanation:
ExamRoom(10) -> null
seat() -> 0, no one is in the room, then the student sits at seat number 0.
seat() -> 9, the student sits at the last seat number 9.
seat() -> 4, the student sits at the last seat number 4.
seat() -> 2, the student sits at the last seat number 2.
leave(4) -> null
seat() -> 5, the student sits at the last seat number 5.
​​​​​​​

Note:

1 <= N <= 10^9
ExamRoom.seat() and ExamRoom.leave() will be called at most 10^4 times across all test cases.
Calls to ExamRoom.leave(p) are guaranteed to have a student currently sitting in seat number p.


*/
#include <set>
using std::set;

class ExamRoom1 {
public:
    ExamRoom1(int N) {
        n = N;
    }
    
    int seat() {
        int start = 0, mx = 0, idx = 0;
        for (int i : spots) {
            if (start == 0) {
                if (mx < i - start) {
                    mx = i - start;
                    idx = 0;
                }
            } else {
                if (mx < (i - start + 1) / 2) {
                    mx = (i - start + 1) / 2;
                    idx = start + mx - 1;
                }
            }
            start = i + 1;
        }
        if (start > 0 && mx < n - start) {
            mx = n - start;
            idx = n - 1;
        }
        spots.insert(idx);
        return idx;
    }
    
    void leave(int p) {
        spots.erase(p);
    }

private:
    int n;
    set<int> spots;
};

class ExamRoom {
public:
    ExamRoom(int N) : N(N) {
        
    }
    
    int seat() {
        // Seat at 0 if all empty
        if (seated.empty()) {
            seated.insert(0);
            return 0;
        }
        
        // Choices:
        // Seat at 0 if vacant
        // Seat at N - 1 if vacant
        // Seat at middle of max width range
        
        // Intialize max dist position and max distance
        int maxPos = 0;
        int maxDist = 0;
        
        // Seat at 0
        if (!seated.count(0)) {
            maxPos = 0;
            maxDist = *seated.begin();
        } 
        
        // Seat in between occupied seats
        auto last = seated.begin();
        
        for (auto it = next(seated.begin()); it != seated.end(); ++it) {
            if (*it == *last + 1) {
                last = it;
                continue;
            }
                
            // New seating position
            int pos = (*it + *last) / 2;
            
            // New distance
            int dist = pos - *last;
               
            // Select this location if bigger dist
            if (dist > maxDist) {
                maxDist = dist;
                maxPos = pos;
            }
                
            last = it;
        }
        
        // Saet at last postion
        if (!seated.count(N - 1)) {
            int dist = N - 1 - *prev(seated.end());
            
            if (dist > maxDist) {
                maxPos = N - 1;
                maxDist = dist;
            } 
        }
        
        // Occupy selected postion
        seated.insert(maxPos);
        
        return maxPos;
    }
    
    void leave(int p) {
        seated.erase(p);
    }
    
private:
    int N;
    set<int> seated;
};