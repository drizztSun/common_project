use std::rc::Rc;
use std::cell::RefCell;
use std::vec::Vec;

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


struct Tree_inorder_travel (u8);

impl Tree_inorder_travel {

    fn inorder_one(root: Option<Rc<RefCell<TreeNode>>>) -> Vec<i32> {

        match root {
            Some(node) => {
                let mut res = vec![];
                let mut buf = vec![];
                buf.push(node.clone());

                while ! buf.is_empty() {
                    let top = buf.pop().unwrap();
                    let mut mut_top = top.borrow_mut();

                    if mut_top.left.is_some() {
                        let left = mut_top.left.take().unwrap();
                        buf.push(top.clone());
                        buf.push(left);
                    } else {
                        res.push(mut_top.val);
                        if mut_top.right.is_some() {
                            buf.push(mut_top.right.take().unwrap());
                        }
                    }
                }
                res
            },
            None => {
                vec![]
            }
        }
    }

    fn inorder_two(root: Option<Rc<RefCell<TreeNode>>>) -> Vec<i32> {

        let mut res = vec![];
        let mut buf = vec![];
        let mut cur = root;

        while cur.is_some() {

            if cur.as_ref().unwrap().borrow().left.is_some() {
                buf.push(cur.clone());
                let m = cur.as_ref().unwrap().borrow().left.clone();
                cur = m;
                continue;
            }

            res.push(cur.as_ref().unwrap().borrow().val);

            while cur.as_ref().unwrap().borrow().right.is_none() && ! buf.is_empty() {
                cur = buf.pop().unwrap();
                res.push(cur.as_ref().unwrap().borrow().val);
            }

            let m = cur.as_ref().unwrap().borrow().right.clone();
            cur = m;
        }

        res
    }

    fn inorder_three(root: Option<Rc<RefCell<TreeNode>>>) -> Vec<i32> {

        fn recur(node: Option<Rc<RefCell<TreeNode>>>) -> Vec<i32> {
            match node {
                Some(n) => {
                    let mut left = recur(n.borrow().left.clone());
                    left.push(n.borrow().val);
                    left.append(&mut recur(n.borrow().right.clone()));
                    left
                },
                None => {
                    vec![]
                }
            }
        }

        recur(root)
    }

    fn inorder_four(root: Option<Rc<RefCell<TreeNode>>>) -> Vec<i32> {

        let mut res = vec![];
        let mut buf = vec![];
        let mut cur = root;

        while ! buf.is_empty() || cur.is_some() {

            if cur.is_some() {
                buf.push(cur.clone());
                let m = cur.as_mut().unwrap().borrow_mut().left.clone();
                cur = m;
            } else {
                cur = buf.pop().unwrap();
                res.push(cur.as_ref().unwrap().borrow().val);
                let m = cur.as_mut().unwrap().borrow_mut().right.clone();
                cur = m;
            }
        }
        res
    }

    fn inorder_four(root: Option<Rc<RefCell<TreeNode>>>) -> Vec<i32> {

        let mut res = vec![];
        let mut buf = vec![];
        let mut cur = root;

        while ! buf.is_empty() || cur.is_some() {

            match cur {
                Some(node) => {
                    buf.push(node.clone());
                    cur = node.borrow().left.clone();
                },
                None => {
                    let node = buf.pop().unwrap();
                    res.push(node.borrow().val);
                    cur = node.borrow().right.clone();
                }
            }
        }
        res
    }
}

pub fn test_94_binary_tree_inorder_travels() {

    let mut root = Some(Rc::new(RefCell::new(TreeNode::new(1))));

    root.as_mut().unwrap().borrow_mut().left = Some(Rc::new(RefCell::new(TreeNode::new(2))));
    root.as_mut().unwrap().borrow_mut().right = Some(Rc::new(RefCell::new(TreeNode::new(5))));

    Tree_inorder_travel::inorder_four(root);
}