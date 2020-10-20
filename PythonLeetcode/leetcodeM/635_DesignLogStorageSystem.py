"""
635. Design Log Storage System

You are given several logs, where each log contains a unique ID and timestamp. Timestamp is a string that has the following format:
Year:Month:Day:Hour:Minute:Second, for example, 2017:01:01:23:59:59. All domains are zero-padded decimal numbers.

Implement the LogSystem class:

LogSystem() Initializes the LogSystem object.
void put(int id, string timestamp) Stores the given log (id, timestamp) in your storage system.
int[] retrieve(string start, string end, string granularity) Returns the IDs of the logs whose timestamps are within the range from start to end inclusive.
start and end all have the same format as timestamp, and granularity means how precise the range should be (i.e. to the exact Day, Minute, etc.).
For example, start = "2017:01:01:23:59:59", end = "2017:01:02:23:59:59", and granularity = "Day" means that we need to find the logs within the inclusive range from Jan. 1st 2017 to Jan. 2nd 2017, and the Hour, Minute, and Second for each log entry can be ignored.


Example 1:

Input
["LogSystem", "put", "put", "put", "retrieve", "retrieve"]
[[], [1, "2017:01:01:23:59:59"], [2, "2017:01:01:22:59:59"], [3, "2016:01:01:00:00:00"], ["2016:01:01:01:01:01", "2017:01:01:23:00:00", "Year"], ["2016:01:01:01:01:01", "2017:01:01:23:00:00", "Hour"]]
Output
[null, null, null, null, [3, 2, 1], [2, 1]]

Explanation
LogSystem logSystem = new LogSystem();
logSystem.put(1, "2017:01:01:23:59:59");
logSystem.put(2, "2017:01:01:22:59:59");
logSystem.put(3, "2016:01:01:00:00:00");

// return [3,2,1], because you need to return all logs between 2016 and 2017.
logSystem.retrieve("2016:01:01:01:01:01", "2017:01:01:23:00:00", "Year");

// return [2,1], because you need to return all logs between Jan. 1, 2016 01:XX:XX and Jan. 1, 2017 23:XX:XX.
// Log 3 is not returned because Jan. 1, 2016 00:00:00 comes before the start of the range.
logSystem.retrieve("2016:01:01:01:01:01", "2017:01:01:23:00:00", "Hour");


Constraints:

1 <= id <= 500
2000 <= Year <= 2017
1 <= Month <= 12
1 <= Day <= 31
0 <= Hour <= 23
0 <= Minute, Second <= 59
granularity is one of the values ["Year", "Month", "Day", "Hour", "Minute", "Second"].
At most 500 calls will be made to put and retrieve.

"""
import collections


class LogSystem:

    def __init__(self):
        self._buf = []
        self.timekey = {"Year": 4, "Month": 7, "Day": 10, "Hour": 13, "Minute": 16, "Second": 19}

    def _search(self, timestamp):
        low, high = 0, len(self._buf)

        while low < high:

            mid = (low + high) // 2

            if self._buf[mid][0] >= timestamp:
                high = mid
            else:
                low = mid + 1

        return low

    def _insert(self, timestamp, val):

        i = self._search(timestamp)

        if len(self._buf) > i and self._buf[i][0] == timestamp:
            self._buf[i][1].append(val)
        else:
            self._buf.insert(i, (timestamp, [val]))

    def put(self, id: int, timestamp: str):

        self._insert(timestamp, id)

    def retrieve(self, start: str, end: str, gra: str):

        i = self.timekey[gra]
        s = start[:i] + "0000:00:00:00:00:00"[i:]
        e = end[:i] + "9999:99:99:99:99:99"[i:]

        res = []
        st = self._search(s)
        end = self._search(e)
        end += 1 if end < len(self._buf) and self._buf[end][0] == e else 0
        for i in range(st, end):
            res.extend(self._buf[i][1])
        return res


class LogSystemI:
    def __init__(self):
        self.c = collections.defaultdict(list)
        self.i = {"Year": 4, "Month": 7, "Day": 10, "Hour": 13, "Minute": 16, "Second": 19}

    def put(self, id, timestamp):
        self.c[timestamp].append(id)

    def retrieve(self, s, e, gra):
        i = self.i[gra]
        s = s[:i] + "0000:00:00:00:00:00"[i:]
        e = e[:i] + "9999:99:99:99:99:99"[i:]
        ret = []
        for t, ids in self.c.items():
            if s <= t <= e:
                ret.extend(ids)
        return ret


if __name__ == '__main__':

    logSystem = LogSystem()

    logSystem.put(1, "2017:01:01:23:59:59")
    logSystem.put(2, "2017:01:01:22:59:59")
    logSystem.put(3, "2016:01:01:00:00:00")

    logSystem.retrieve("2016:01:01:01:01:01", "2017:01:01:23:00:00", "Year")
    logSystem.retrieve("2016:01:01:01:01:01", "2017:01:01:23:00:00", "Hour")

    l2 = LogSystem()

    l2.put(1, "2017:01:01:23:59:59")
    l2.put(2, "2017:01:02:23:59:59")

    l2.retrieve("2017:01:01:23:59:59", "2017:01:02:23:59:59", "Second")
