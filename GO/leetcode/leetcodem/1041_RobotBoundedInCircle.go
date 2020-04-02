package leetcodem

/*

1041. Robot Bounded In Circle

On an infinite plane, a robot initially stands at (0, 0) and faces north.  The robot can receive one of three instructions:

"G": go straight 1 unit;
"L": turn 90 degrees to the left;
"R": turn 90 degress to the right.
The robot performs the instructions given in order, and repeats them forever.

Return true if and only if there exists a circle in the plane such that the robot never leaves the circle.

 

Example 1:

Input: "GGLLGG"
Output: true
Explanation: 
The robot moves from (0,0) to (0,2), turns 180 degrees, and then returns to (0,0).
When repeating these instructions, the robot remains in the circle of radius 2 centered at the origin.
Example 2:

Input: "GG"
Output: false
Explanation: 
The robot moves north indefinitely.
Example 3:

Input: "GL"
Output: true
Explanation: 
The robot moves from (0, 0) -> (0, 1) -> (-1, 1) -> (-1, 0) -> (0, 0) -> ...

*/

func isRobotBounded(instructions string) bool {

    pos := []int{0, 0, 0}
	direct := [][]int{[]int{0, 1}, []int{-1, 0}, []int{0, -1}, []int{1, 0}}

	for _, c := range instructions {

		if c == 'G' {
			pos[0] += direct[pos[2]][0]
			pos[1] += direct[pos[2]][1]
		} else if c == 'L' {
			pos[2] = (pos[2] + 1 ) % 4
		} else if c == 'R' {
			pos[2] = (4 + pos[2] - 1) % 4
		}
	}

    if pos[2] == 1 && (pos[0] != 0 || pos[1] != 0) {
		return false
	}

	return true
}

func Test_1041_RobotBoundledInCircle() {

	isRobotBounded("GG")

	isRobotBounded("GGLLGG")

	isRobotBounded("GL")
}