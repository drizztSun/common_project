/*
407. Trapping Rain Water II

Given an m x n matrix of positive integers representing the height of each unit cell in a 2D elevation map, compute the volume of water it is able to trap after raining.

Example:

Given the following 3x6 height map:
[
  [1,4,3,1,3,2],
  [3,2,1,3,2,4],
  [2,3,3,2,3,1]
]

Return 4.
*/


impl Solution {
    fn get_directions_from_pt(
        height_map: &Vec<Vec<i32>>,
        row: usize,
        col: usize,
    ) -> Vec<(usize, usize)> {
        let mut directions: Vec<(usize, usize)> = vec![];
        if row > 0 {
            directions.push((row - 1, col));
        }
        if row < height_map.len() - 1 {
            directions.push((row + 1, col));
        }
        if col > 0 {
            directions.push((row, col - 1));
        }
        if col < height_map[row].len() - 1{
            directions.push((row, col + 1));
        }
        directions
    }

    pub fn trap_rain_water(height_map: Vec<Vec<i32>>) -> i32 {
        use std::cmp::{max, Reverse};
        use std::collections::BinaryHeap;

        let mut curr_max = -1;

        // Build `visited` map
        let mut visited: Vec<Vec<bool>> = vec![];
        for r in 0..height_map.len() {
            let row: Vec<bool> = vec![false; height_map[r].len()];
            visited.push(row);
        }

        // Populate Min-Heap with Boundary first
        let mut min_heap = BinaryHeap::new();
        for r in 0..height_map.len() {
            for c in 0..height_map[r].len() {
                if r > 0 && r < height_map.len() - 1 && c > 0 && c < height_map[r].len() - 1 {
                    continue
                }
                visited[r][c] = true;
                min_heap.push(Reverse((height_map[r][c], r, c)));
            }
        }

        let mut volume = 0;
        while min_heap.len() > 0 {
            match min_heap.pop() {
                Some(node) => {
                    let height = (node.0).0;
                    let row = (node.0).1;
                    let col = (node.0).2;

                    curr_max = max(curr_max, height);
                    let directions = Solution::get_directions_from_pt(&height_map, row, col);
                    for direction in directions.iter() {
                        let next_row = direction.0;
                        let next_col = direction.1;

                        if visited[next_row][next_col] {
                            continue;
                        }
                        
                        volume += max(0, curr_max - height_map[next_row][next_col]);
                        visited[next_row][next_col] = true;
                        min_heap.push(Reverse((
                            height_map[next_row][next_col],
                            next_row,
                            next_col,
                        )));
                    }
                }
                None => {
                    unreachable!();
                }
            }
        }

        volume
    }
}