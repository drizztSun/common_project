# 551. Student Attendance Record I

# You are given a string representing an attendance record for a student. The record only contains the following three characters:
# 'A' : Absent.
# 'L' : Late.
# 'P' : Present.
# A student could be rewarded if his attendance record doesn't contain more than one 'A' (absent) or more than two continuous 'L' (late).

# You need to return whether the student could be rewarded according to his attendance record.

# Example 1:
# Input: "PPALLP"
# Output: True

# Example 2:
# Input: "PPALLL"
# Output: False

class StudentAttendanceRecord(object):
    def doit(self, s):
        """
        :type s: str
        :rtype: bool
        """
        L, A = 0, 0
        for c in s:
            if c == 'L':
                L += 1
            else:
                L = 0
                
            if c == 'A':
                A += 1
            
            
                
            if L == 3 or A == 2:
                return False
        
        return True


if __name__ == "__main__":

    res = StudentAttendanceRecord().doit("PPALLP")

    res = StudentAttendanceRecord().doit("PPALLL")