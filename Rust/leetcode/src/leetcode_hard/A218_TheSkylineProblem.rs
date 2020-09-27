/*

218. The Skyline Problem

A city's skyline is the outer contour of the silhouette formed by all the buildings in that city when viewed from a distance.
Now suppose you are given the locations and height of all the buildings as shown on a cityscape photo (Figure A), write a program to output the skyline formed by these buildings collectively (Figure B).

The geometric information of each building is represented by a triplet of integers [Li, Ri, Hi], where Li and Ri are the x coordinates of the left and right edge of the ith building, respectively, and Hi is its height.
It is guaranteed that 0 ≤ Li, Ri ≤ INT_MAX, 0 < Hi ≤ INT_MAX, and Ri - Li > 0. You may assume all buildings are perfect rectangles grounded on an absolutely flat surface at height 0.

For instance, the dimensions of all buildings in Figure A are recorded as: [ [2 9 10], [3 7 15], [5 12 12], [15 20 10], [19 24 8] ] .

The output is a list of "key points" (red dots in Figure B) in the format of [ [x1,y1], [x2, y2], [x3, y3], ... ] that uniquely defines a skyline. A key point is the left endpoint of a horizontal line segment.
Note that the last key point, where the rightmost building ends, is merely used to mark the termination of the skyline, and always has zero height.
Also, the ground in between any two adjacent buildings should be considered part of the skyline contour.

For instance, the skyline in Figure B should be represented as:[ [2 10], [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0] ].

Notes:

The number of buildings in any input list is guaranteed to be in the range [0, 10000].
The input list is already sorted in ascending order by the left x position Li.
The output list must be sorted by the x position.
There must be no consecutive horizontal lines of equal height in the output skyline. For instance, [...[2 3], [4 5], [7 5], [11 5], [12 7]...] is not acceptable;
the three lines of height 5 should be merged into one in the final output as such: [...[2 3], [4 5], [12 7], ...]

*/
use std::cmp::Ordering;
use std::collections::BinaryHeap;


#[derive(Copy, Clone, Eq, PartialEq)]
struct skylinePos{
    pos: i32,
    height: i32,
}

// The priority queue depends on `Ord`.
// Explicitly implement the trait so the queue becomes a min-heap
// instead of a max-heap.
impl Ord for skylinePos {

    fn cmp(&self, other: &skylinePos) -> Ordering {
        self.height.cmp(&other.height).then_with(|| self.pos.cmp(&other.pos))
    }
}

impl PartialOrd for skylinePos {
    fn partial_cmp(&self, other: &skylinePos) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

struct Skyline (u8);

impl Skyline {

    pub fn doit_heap(buildings: Vec<Vec<i32>>) -> Vec<Vec<i32>> {

        let mut heap: BinaryHeap<skylinePos> = BinaryHeap::new();
        let mut i = 0;
        let mut skyline: Vec<Vec<i32>> = vec![];

        let mut buildings = buildings;
        buildings.sort_by(|a, b| a.partial_cmp(b).unwrap());


        while i < buildings.len() || ! heap.is_empty() {

            let mut x = 0;

            if heap.is_empty() || i < buildings.len() && heap.peek().unwrap().pos >= buildings[i][0] {

                x = buildings[i][0];
                while i < buildings.len() &&  buildings[i][0] <= x {
                    heap.push(skylinePos{pos: buildings[i][1], height: buildings[i][2]});
                    i += 1;
                }
            } else {

                x = heap.peek().unwrap().pos;
                while !heap.is_empty() && heap.peek().unwrap().pos <= x {
                    heap.pop();
                }
            }

            let mut height = 0;
            if heap.len() > 0 {
                height = heap.peek().unwrap().height;
            }

            if skyline.is_empty() || height != skyline[skyline.len() - 1][1] {
                skyline.push(vec![x, height]);
            }
        }

        skyline
    }
}


pub fn test_218_skyline() {

    Skyline::doit_heap(vec![vec![2, 9, 10], vec![3, 7, 15], vec![5, 12, 12], vec![15, 20, 10], vec![19, 24, 8]]);
}