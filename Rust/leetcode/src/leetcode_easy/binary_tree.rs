// Definition for a binary tree node.
// #[derive(Debug, PartialEq, Eq)]
// pub struct TreeNode {
//   pub val: i32,
//   pub left: Option<Rc<RefCell<TreeNode>>>,
//   pub right: Option<Rc<RefCell<TreeNode>>>,
// }
// 
// impl TreeNode {
//   #[inline]
//   pub fn new(val: i32) -> Self {
//     TreeNode {
//       val,
//       left: None,
//       right: None
//     }
//   }
// }
use std::rc::Rc;
use std::cell::RefCell;
use std::vec;

#[derive(Debug, PartialEq, Eq)]
struct TreeNode {
    pub val: i32,
    pub left: Option<Rc<RefCell<TreeNode>>>,
    pub right: Option<Rc<RefCell<TreeNode>>>,
}

impl TreeNode {
    pub fn new(val: i32) -> Self {
        TreeNode{
            val: val,
            left: None,
            right: None,
        }
    }
}


pub fn inorder_traversal(root: Option<Rc<RefCell<TreeNode>>>) -> Vec<i32> {

    let mut buff = vec![];
    let mut result = vec![];


    match root {
        Some(node) => {
            buff.push(node.clone());
            while !buff.is_empty() {
                let top = buff.pop().unwrap();
                let mut mut_top = top.borrow_mut();

                if mut_top.left.is_some() {
                    let left = mut_top.left().take().unwrap();
                }
            }

        },

        None => {
            result
        }
    }

    return result
}    





pub fn test_binary_tree() {

    let root = Some(Rc::new(RefCell::new(TreeNode::new(1))));
    // root.left = TreeNode::new(2);
    root.as_mut().right = Some(Rc::new(RefCell::new(TreeNode::new(3))));

    let a = inorder_traversal(root);

}