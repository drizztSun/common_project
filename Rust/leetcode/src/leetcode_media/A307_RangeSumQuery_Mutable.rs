use std::vec::Vec;
use std::rc::Rc;
use std::cell::RefCell;

struct segmentNode {
    start: usize,
    end: usize,
    sum: i32,

    left: Option<Rc<RefCell<segmentNode>>>,
    right: Option<Rc<RefCell<segmentNode>>>,
}

struct NumArray {
    root: Option<Rc<RefCell<segmentNode>>>,
}


/** 
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl NumArray {
    

    fn build(nums: &Vec<i32>, s: usize, e: usize) -> Option<Rc<RefCell<segmentNode>>> {
        
        if nums.len() == 0 {
            return None
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


    fn new(nums: Vec<i32>) -> Self {
        NumArray{root: Self::build(&nums, 0, (nums.len()-1) as usize)}
    }
    
    fn update(&self, i: i32, val: i32) {
        Self::update_segment(self.root.clone(), i as usize, val);
    }
    
    fn sum_range(&self, i: i32, j: i32) -> i32 {
        Self::sum_segment(self.root.clone(), i as usize, j as usize)
    }
}