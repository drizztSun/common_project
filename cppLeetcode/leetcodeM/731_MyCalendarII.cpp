/*
731. My Calendar II


Implement a MyCalendarTwo class to store your events. A new event can be added if adding the event will not cause a triple booking.

Your class will have one method, book(int start, int end). Formally, this represents a booking on the half open interval [start, end), the range of real numbers x such that start <= x < end.

A triple booking happens when three events have some non-empty intersection (ie., there is some time that is common to all 3 events.)

For each call to the method MyCalendar.book, return true if the event can be added to the calendar successfully without causing a triple booking. Otherwise, return false and do not add the event to the calendar.

Your class will be called like this: MyCalendar cal = new MyCalendar(); MyCalendar.book(start, end)
Example 1:

MyCalendar();
MyCalendar.book(10, 20); // returns true
MyCalendar.book(50, 60); // returns true
MyCalendar.book(10, 40); // returns true
MyCalendar.book(5, 15); // returns false
MyCalendar.book(5, 10); // returns true
MyCalendar.book(25, 55); // returns true
Explanation: 
The first two events can be booked.  The third event can be double booked.
The fourth event (5, 15) can't be booked, because it would result in a triple booking.
The fifth event (5, 10) can be booked, as it does not use time 10 which is already double booked.
The sixth event (25, 55) can be booked, as the time in [25, 40) will be double booked with the third event;
the time [40, 50) will be single booked, and the time [50, 55) will be double booked with the second event.
 

Note:

The number of calls to MyCalendar.book per test case will be at most 1000.
In calls to MyCalendar.book(start, end), start and end are integers in the range [0, 10^9].

*/
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using std::multiset;
using std::multimap;
using std::vector;

/*
    731.My-Calendar-II
    不需要考虑有序Hash和迭代器。此题只要找出所有与[start,end)重合的区间，再检查这些区间是否有互相的重合。是的话，说明必然有triple booking。
*/

class MyCalendarTwo {

    vector<std::pair<int,int>>events;
public:
    MyCalendarTwo() {}
    
    bool book(int start, int end) 
    {
        vector<std::pair<int,int>>temp;
        for (int i=0; i<events.size(); i++)
        {
            if (!(events[i].second<=start || events[i].first>=end))
                temp.push_back(events[i]);
        }
        std::sort(temp.begin(),temp.end());
        
        for (int i=1; i<temp.size(); i++)
        {
            if (temp[i].first<temp[i-1].second)
                return false;
        }
        
        events.push_back({start,end});        

        return true;
    }
};

class MyCalendarTwo {

    multiset<std::pair<int,int>>Set;

public:
    MyCalendarTwo() {}
    
    bool book(int start, int end) 
    {
        vector<std::pair<int,int>> p;

        for (auto x: Set)
        {
            if (!(end<=x.first || start>=x.second))
                p.push_back(x);
            if (end<=x.first) break;
        }

        for (int i=1; i<p.size(); i++)
        {
            if (p[i].first<p[i-1].second)
                return false;
        }
        
        Set.insert({start,end});
        return true;
    }
};


class MyCalendarTwo {
    
	vector<std::pair<int, int>> calendar_;
	vector<std::pair<int, int>> overlap_;

public:
	MyCalendarTwo() {}

	bool book(int start, int end) {

		for (auto& p : overlap_)
			if (start < p.second && end > p.first)
				return false;

		for (auto& p : calendar_) {
			if (start < p.second && end > p.first) {
				overlap_.push_back({std::max(start, p.first), std::min(end, p.second)});
			}
		}

		calendar_.push_back({start, end});

		return true;
	}
};