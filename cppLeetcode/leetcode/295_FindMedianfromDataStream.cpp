/*

# 295. Find Median from Data Stream


#Median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value.
# So the median is the mean of the two middle value.

# Examples:
# [2,3,4] , the median is 3

# [2,3], the median is (2 + 3) / 2 = 2.5

# Design a data structure that supports the following two operations:

# void addNum(int num) - Add a integer number from the data stream to the data structure.
# double findMedian() - Return the median of all elements so far.
# For example:

# addNum(1)
# addNum(2)
# findMedian() -> 1.5
# addNum(3)
# findMedian() -> 2




I keep two heaps (or priority queues):

Max-heap small has the smaller half of the numbers.
Min-heap large has the larger half of the numbers.
This gives me direct access to the one or two middle values (they’re the tops of the heaps), so getting the median takes O(1) time. And adding a number takes O(log n) time.

Supporting both min- and max-heap is more or less cumbersome, depending on the language, so I simply negate the numbers in the heap in which I want the reverse of the default order. To prevent this from causing a bug with -231 (which negated is itself, when using 32-bit ints), I use integer types larger than 32 bits.

Using larger integer types also prevents an overflow error when taking the mean of the two middle numbers. I think almost all solutions posted previously have that bug.

Update: These are pretty short already, but by now I wrote even shorter ones.


*/

#include <stdlib.h>
#include <queue>
#include <vector>

using namespace std;

class MedianFinder {

	std::priority_queue<double> smaller_, larger_;
	bool even_;

public:

	MedianFinder(): even_(true) {

	}

	void addNum(int num) {
		if (even_) {
			smaller_.push(num);
			larger_.push(- smaller_.top());
			smaller_.pop();
		}
		else {
			larger_.push(-num);
			smaller_.push(-larger_.top());
			larger_.pop();
		}

		even_ = !even_;
	}

    double findMedian() {
        if (even_) {
            return double(smaller_.top() - larger_.top()) / 2;
        }
        else {
            return -larger_.top();
        }
    }
};

class MedianFinder3
{
public:
    priority_queue<int> g;
    priority_queue<int, vector<int>, greater<int>> l;

    void addNum(int num)
    {
        if (g.empty() || g.top() > num)
        {
            g.push(num); //1
        }
        else
        {
            l.push(num); //2 3
        }

        if (g.size() > l.size() + 1)
        {
            l.push(g.top());
            g.pop();
        }
        else if (l.size() > g.size() + 1)
        {
            g.push(l.top());
            l.pop();
        }
    }

    double findMedian()
    {

        if (g.size() == l.size())
        {
            return double((g.top() + l.top()) / 2.0);
        }
        if (g.size() > l.size())
            return g.top();

        return l.top();
    }
};


class MedianFinder2 {
public:
    /** initialize your data structure here. */
    MedianFinder2() {
        
    }
    
    void addNum(int num) {
        auto it = std::lower_bound(_src.begin(), _src.end(), num);
        _src.insert(it, num);
    }
    
    double findMedian() {
        size_t cnt = _src.size();
        if (cnt % 2 == 0) {
            return double(_src[(cnt-1)/2] + _src[(cnt-1)/2+1]) / 2;
        } else {
            return _src[(cnt-1)/2];
        }
    }
private:
    
    vector<int> _src;

};


class MedianFinder1 {
public:
	/** initialize your data structure here. */
	MedianFinder1() : _count(0) {

	}

	void addNum(int num) {
		//cout << "\nAdding = " << num;
		if (_count == 0) {
			_lowerNumbers.push(num);
		}
		else {
			const int maxLower = _lowerNumbers.top();
			//const int minHigher = _higherNumbers.empty()? (): _higherNumbers.top();
			if (num <= maxLower) {
				if (_lowerNumbers.size() > _higherNumbers.size()) {
					//Already greater than the higher number set
					_higherNumbers.push(maxLower);
					_lowerNumbers.pop();
				}
				_lowerNumbers.push(num);
				//cout << "\nTop of lower =" << _lowerNumbers.top(); 
			}
			else {
				//Goes to the higher numbers queue
				_higherNumbers.push(num);
				if (_higherNumbers.size() > _lowerNumbers.size() + 1) {
					_lowerNumbers.push(_higherNumbers.top());
					_higherNumbers.pop();
				}
			}
		}
		++_count;
	}

	double findMedian() {
		double median = 0;
		if (_count > 0) {
			if (_count % 2 == 0) {
				//Even number of elements
				median = (double)(_lowerNumbers.top() + _higherNumbers.top()) / 2;
			}
			else {
				//Odd number of elements
				median = (_lowerNumbers.size() > _higherNumbers.size()) ? _lowerNumbers.top() : _higherNumbers.top();
			}
		}
		return median;
	}

private:
	struct minHeapCompare {
		bool operator() (const int &a, const int &b) {
			return (a > b);
		}
	};

	typedef std::priority_queue<int, vector<int>/*, std::less<int>*/> maxHeap;
	typedef std::priority_queue<int, vector<int>, minHeapCompare> minHeap;

	maxHeap _lowerNumbers;
	minHeap  _higherNumbers;
	unsigned _count;
};


void Test_295_FindMedianFromDataStream() {

	MedianFinder2 A;

	A.addNum(1);
	A.addNum(2);

	auto res = A.findMedian();

	A.addNum(3);
	res = A.findMedian();

	return;
}
