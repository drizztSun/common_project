/*
729. My Calendar I

Implement a MyCalendar class to store your events. A new event can be added if adding the event will not cause a double booking.

Your class will have the method, book(int start, int end). Formally, this represents a booking on the half open interval [start, end), the range of real numbers x such that start <= x < end.

A double booking happens when two events have some non-empty intersection (ie., there is some time that is common to both events.)

For each call to the method MyCalendar.book, return true if the event can be added to the calendar successfully without causing a double booking. Otherwise, return false and do not add the event to the calendar.

Your class will be called like this: MyCalendar cal = new MyCalendar(); MyCalendar.book(start, end)
Example 1:

MyCalendar();
MyCalendar.book(10, 20); // returns true
MyCalendar.book(15, 25); // returns false
MyCalendar.book(20, 30); // returns true
Explanation: 
The first event can be booked.  The second can't because time 15 is already booked by another event.
The third event can be booked, as the first event takes every time less than 20, but not including 20.
 

Note:

The number of calls to MyCalendar.book per test case will be at most 1000.
In calls to MyCalendar.book(start, end), start and end are integers in the range [0, 10^9].
 

*/
#include <vector>
#include <algorithm>
#include <map>

using std::map;
using std::vector;

class MyCalendar {
    
	vector<int> starts_, ends_;

public:
	MyCalendar() {

	}

	bool book(int start, int end) {

		auto s = lower_bound(starts_.begin(), starts_.end(), start);
		auto steps = distance(starts_.begin(), s);

		if ((steps > 0 && ends_[steps - 1] > start) || (steps < starts_.size() && start < ends_[steps] && end > starts_[steps]))
			return false;

		starts_.insert(s, start);
		ends_.insert(steps + ends_.begin(), end);

		return true;
	}
};


/*
729.My-Calendar-I
此题是训练C++里使用有序容器数据结构（比如说map，set等）基本功的一道题。

首先，使用Map.upper_bound(start)找到第一个大于start的迭代器iter，检查其对应的区间[a,b)是否与[start,end)重合。记得前提是iter有意义，也就是iter!=Map.end().

接着，将iter回退一个位置，找到第一个小于等于start的迭代器，检查其对应的区间[a,b)是否与[start,end)重合。同样，记得前提是此时的iter有意义，也就是iter!=Map.begin().

*/

class MyCalendar {

    map<int,int>Map;
public:
    MyCalendar() {
        
    }
    
    bool book(int start, int end) 
    {
        auto iter1 = Map.upper_bound(start);
        if (iter1!=Map.begin())
        {
            auto iter2 = prev(iter1,1);
            if (iter2->second > start)
                return false;
        }
        if (iter1 != Map.end())
        {
            if (iter1->first < end)
                return false;
        }
        Map[start] = end;
        return true;
    }
};