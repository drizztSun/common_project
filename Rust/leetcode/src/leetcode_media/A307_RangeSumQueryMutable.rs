/*
307. Range Sum Query - Mutable

Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

The update(i, val) function modifies nums by updating the element at index i to val.

Example:

Given nums = [1, 3, 5]

sumRange(0, 2) -> 9
update(1, 2)
sumRange(0, 2) -> 8


Constraints:

The array is only modifiable by the update function.
You may assume the number of calls to update and sumRange function is distributed evenly.
0 <= i <= j <= nums.length - 1
*/
use std::vec::Vec;
use std::rc::Rc;
use std::cell::RefCell;


struct TreeNode<T> {
    value: T,
    left: Option<Rc<RefCell<TreeNode<T>>>>,
    right: Option<Rc<RefCell<TreeNode<T>>>>,
}

type SegmentTreeNode = TreeNode<(i32, usize, usize)>;

impl SegmentTreeNode {
    pub fn new(array: &[i32]) -> Option<Rc<RefCell<Self>>> {
        return Self::inner(array, 0, array.len());
    }
    
    fn inner(array: &[i32], left: usize, right: usize) -> Option<Rc<RefCell<Self>>> {
        if left == right {
            return None;
        } else if left + 1 == right {
            return Some(Rc::new(RefCell::new(Self {
                value: (array[left], left, right),
                left: None,
                right: None,
            })));
        }
    
        let length = right - left;
        let mut res = Self {
            value: (0, left, right),
            left: Self::inner(array, left, left + length / 2),
            right: Self::inner(array, left + length / 2, right),
        };
        res.value.0 = res.left.as_ref().unwrap().borrow().value.0 + res.right.as_ref().unwrap().borrow().value.0;
        return Some(Rc::new(RefCell::new(res)));
    }

    pub fn sum(&self, left: usize, right: usize) -> i32 {
        let (sum, start, end) = self.value;
        if left == start && right == end {
            return sum;
        } else if right <= start || left >= end {
            return 0;
        } else {
            let middle = (start + end) / 2;
            if right <= middle {
                return self.left.as_ref().unwrap().borrow().sum(left, right);
            } else if left >= middle {
                return self.right.as_ref().unwrap().borrow().sum(left, right);
            } else {
                return self.left.as_ref().unwrap().borrow().sum(left, middle)
                    + self.right.as_ref().unwrap().borrow().sum(middle, right);
            }
        }
    }

    pub fn insert(&mut self, index: usize, value: i32) {
        let (sum, start, end) = self.value;
        if start == index && end == index + 1 {
            self.value.0 = value;
        } else {
            let middle = (start + end) / 2;
            if index < middle {
                self.left
                    .as_ref()
                    .unwrap()
                    .borrow_mut()
                    .insert(index, value);
            } else {
                self.right
                    .as_ref()
                    .unwrap()
                    .borrow_mut()
                    .insert(index, value);
            }
            self.value.0 = self.left.as_ref().unwrap().borrow().value.0
                + self.right.as_ref().unwrap().borrow().value.0;
        }
    }
}

struct NumArray {
    tree: Option<Rc<RefCell<SegmentTreeNode>>>,
}

impl NumArray {
    fn new(nums: Vec<i32>) -> Self {
        if nums.is_empty() {
            return Self { tree: None };
        } else {
            return Self {
                tree: SegmentTreeNode::new(&nums[..]),
            };
        }
    }

    fn update(&mut self, i: i32, val: i32) {
        self.tree
            .as_ref()
            .unwrap()
            .borrow_mut()
            .insert(i as usize, val);
    }

    fn sum_range(&self, i: i32, j: i32) -> i32 {
        let i = i as usize;
        let j = j as usize + 1;
        return self.tree.as_ref().unwrap().borrow().sum(i, j);
    }
}


struct segmentNode {
    start: usize,
    end: usize,
    sum: i32,

    left: Option<Rc<RefCell<segmentNode>>>,
    right: Option<Rc<RefCell<segmentNode>>>,
}


struct NumArraySeg {
    root: Option<Rc<RefCell<segmentNode>>>,
}

impl NumArraySeg {

    fn build(nums: &Vec<i32>, s: usize, e: usize) -> Option<Rc<RefCell<Self>>> {

        if nums.len() == 0 {
            return None;
        }

        let mut cur = Rc::new(RefCell::new(segmentNode{start:s,
                                            end:e,
                                            sum:0, left:None, right:None}));
        if s == e {
            cur.borrow_mut().sum = nums[s];
            return Some(cur);
        }

        let mid = (s + e) / 2;



        cur.borrow_mut().left = Self::build(nums, s, mid);
        cur.borrow_mut().right = Self::build(nums, mid+1, e);
        let sum = cur.borrow().left.as_ref().unwrap().borrow().sum + cur.borrow().right.as_ref().unwrap().borrow().sum;
        cur.borrow_mut().sum = sum;

        //cur.borrow_mut().sum = cur.borrow_mut().left.as_ref().unwrap().borrow().sum + cur.borrow_mut().right.as_ref().unwrap().borrow().sum;
        return Some(cur);
    }

    fn sum_segment(n: Option<Rc<RefCell<segmentNode>>>, s: usize, e:usize) -> i32 {

        match n {
            Some(node) => {
                if node.borrow().start == s && node.borrow().end == e {
                    return node.borrow().sum;
                }

                let mid = (node.borrow().start + node.borrow().end) / 2;

                if mid >= e {
                    Self::sum_segment(node.borrow().left.clone(), s, e)
                } else if s >= mid+1 {
                    Self::sum_segment(node.borrow().right.clone(), s, e)
                } else {
                    Self::sum_segment(node.borrow().left.clone(), s, mid) + Self::sum_segment(node.borrow().right.clone(), mid+1, e)
                }
            },
            None => {
                0
            }
        }
    }

    fn update_segment(n: Option<Rc<RefCell<segmentNode>>>, i: usize, val: i32) {
        match n {
            Some(node) => {
                if node.borrow().start == i && node.borrow().end == i {
                    node.borrow_mut().sum = val;
                    return
                }

                let mid = (node.borrow().start + node.borrow().end) / 2;
                if mid >= i {
                    Self::update_segment(node.borrow().left.clone(), i, val);
                } else {
                    Self::update_segment(node.borrow().right.clone(), i, val);
                }
                let sum = node.borrow().left.as_ref().unwrap().borrow().sum + node.borrow().right.as_ref().unwrap().borrow().sum;
                node.borrow_mut().sum = sum;
            },
            None => {}
        }
    }


    pub fn new(nums: Vec<i32>) -> Self {
        NumArraySeg{root: Self::build(&nums, 0, nums.len()-1)}
    }



    pub fn update(&mut self, i: usize, val: i32) {
        Self::update_segment(self.root.clone(), i, val);
    }

    pub fn sum_range(& self, s: usize, e: usize) -> i32 {
        Self::sum_segment(self.root.clone(), s, e)
    }
}


// BIT solution
struct NumArrBit {
    nums: Vec<i32>,
    e: Vec<i32>,
}


impl NumArrBit {

    fn new(nums: Vec<i32>) -> Self {

        let N = nums.len();
        let mut e = vec![0; N+1];

        for i in 1..(N+1){
            let mut p = i as i32;
            e[i] += nums[i-1];
            p += p & (-p);
            if p <= N as i32 {
                e[p as usize] += e[i];
            }
        }

        NumArrBit{nums, e}
    }

    fn update(&mut self, i: i32, val: i32) {

        let diff = val - self.nums[i as usize] as i32;
        let mut p = i + 1;
        self.nums[i as usize] = val;

        while p < self.e.len() as i32 {
            self.e[p as usize] += diff;
            p += p & (-p);
        }
    }

    fn sum(&self, i: i32) -> i32 {

        let mut res = 0;
        let mut p = i + 1;

        while p > 0 {
            res += self.e[p as usize];
            p -= p & (-p);
        }

        res
    }

}

struct NumArray {
    bitTree: NumArrBit,
}

impl NumArray {

    fn new(nums: Vec<i32>) -> Self {
        return NumArray{bitTree: NumArrBit::new(nums)};
    }

    fn update(&mut self, i: i32, val: i32) {
        self.bitTree.update(i, val);
    }

    fn sum_range(&self, i: i32, j: i32) -> i32 {
        self.bitTree.sum(j) - self.bitTree.sum(i-1)
    }
}


pub fn test_307_RangeSumQueryMutable() {

    let mut obj = NumArraySeg::new(vec![1, 3, 5]);

    println!("R: {}", obj.sum_range(0, 2));

    obj.update(1, 2);

    println!("R: {}", obj.sum_range(0, 2));


    let mut obj1 = NumArraySeg::new(vec![0, 9, 5, 7, 3]);

    println!("{}", obj1.sum_range(4, 4));

    println!("{}", obj1.sum_range(2, 4));

    println!("{}", obj1.sum_range(3, 3));

}