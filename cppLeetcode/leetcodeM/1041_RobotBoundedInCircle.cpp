

/*
 
 # 1041. Robot Bounded In Circle

 # On an infinite plane, a robot initially stands at (0, 0) and faces north.
 # The robot can receive one of three instructions:

 # "G": go straight 1 unit;
 # "L": turn 90 degrees to the left;
 # "R": turn 90 degress to the right.
 # The robot performs the instructions given in order, and repeats them forever.

 # Return true if and only if there exists a circle in the plane such that the robot never leaves the circle.


 # Example 1:

 # Input: "GGLLGG"
 # Output: true
 # Explanation:
 # The robot moves from (0,0) to (0,2), turns 180 degrees, and then returns to (0,0).
 # When repeating these instructions, the robot remains in the circle of radius 2 centered at the origin.

 # Example 2:

 # Input: "GG"
 # Output: false
 # Explanation:
 # The robot moves north indefinitely.

 # Example 3:

 # Input: "GL"
 # Output: true
 # Explanation:
 # The robot moves from (0, 0) -> (0, 1) -> (-1, 1) -> (-1, 0) -> (0, 0) -> ...

 # Note:

 # 1 <= instructions.length <= 100
 # instructions[i] is in {'G', 'L', 'R'}
 
 */

#include <string>

using std::string;


class IsRobotBounded {
public:
    bool doit(string instructions) {
        
        int lcnt = 0, rcnt = 0, gcnt = 0;
        int face = 0;
        int pos[2];
        pos[0] = 0, pos[1] = 0;
        
        for (auto c : instructions) {
            
            if (c == 'G') {
                gcnt++;
                pos[face % 2] += face < 2 ? 1 : -1;
            } else if (c == 'L') {
                lcnt++;
                face = (face + 3) % 4;
            } else if (c == 'R') {
                rcnt++;
                face = (face + 1) % 4;
            }
        }
        
        if ((lcnt - rcnt) % 4)
            return true; // not facing north -> goes back and forth or in square
        
        if (gcnt % 2)
            return false; // still facing north and cannot be back to origin
        
        return pos[0] == 0 && pos[1] == 0; // get to the origin point
    }
};


void test_1041_robot_bounded_in_circle() {
    
    auto res1 = IsRobotBounded().doit("GGLLGG");
    
    auto res2 = IsRobotBounded().doit("GG");
    
    auto res3 = IsRobotBounded().doit("GL");
    
    auto res4 = IsRobotBounded().doit("RLLGGLRGLGLLLGRLRLRLRRRRLRLGRLLLGGL");
    
    return;
}

