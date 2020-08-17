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

fn inorder_one(root: Option<Rc<RefCell<TreeNode>>>) -> Vec<i32> {
    let node = match root {
        Some(n) => n,
        None => return vec![],
    };

    let mut buff = vec![];
    let mut res = vec![];

    buff.push((node, false));

    while let Some((node, left_checked)) = buff.pop() {
        if ! left_checked {
            buff.push((node.clone(), true));
            if let Some(left) = node.borrow().left.clone() {
                buff.push((left.clone(), false));
            }
        } else {
            res.push(node.borrow().val);
            if let Some(right) = node.borrow().right.clone() {
                buff.push((right.clone(), false));
            }
        }
    }

    res
}

fn inorder_recur(root: Option<Rc<RefCell<TreeNode>>>) -> Vec<i32> {

    fn helper(node: &Option<Rc<RefCell<TreeNode>>>, res: &mut Vec<i32>) {
        if let Some(v) = node {
            let v = v.borrow();
            helper(&v.left, res);
            res.push(v.val);
            helper(&v.right, res);
        }
    }

    let mut res = vec![];
    if let Some(node) = root {
        helper(&Some(node), &mut res);
    }
    res
}

fn inorder_traversal(root: Option<Rc<RefCell<TreeNode>>>) -> Vec<i32> {

    let mut res = vec![];
    let mut stack = vec![];

    match root {
        Some(node) => {
            stack.push(node.clone());
            while !stack.is_empty() {
                let top = stack.pop().unwrap();
                let mut top_mut = top.borrow_mut();

                if top_mut.left.is_some() {
                    let left = top_mut.left.take().unwrap();
                    stack.push(top.clone());
                    stack.push(left);
                } else {
                    res.push(top_mut.val);
                    if top_mut.right.is_some() {
                        stack.push(top_mut.right.take().unwrap());
                    }
                }
            }
            res
        },
        None => {
            res
        }
    }    
}

fn dfs(root: Option<Rc<RefCell<TreeNode>>>) {

    if let Some(root) = root {
        let root = root.borrow();

        dfs(root.left.clone());

        dfs(root.right.clone());
    }
}

pub fn test_binary_tree() {

    let root = Rc::new(RefCell::new(TreeNode::new(1)));
    root.borrow_mut().left = Some(Rc::new(RefCell::new(TreeNode::new(2))));
    root.borrow_mut().right = Some(Rc::new(RefCell::new(TreeNode::new(3))));

    let _res = inorder_traversal(Some(root));

}