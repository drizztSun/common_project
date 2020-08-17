use std::rc::Rc;
use std::cell::RefCell;

// Definition for a binary tree node.
#[derive(Debug, PartialEq, Eq)]
pub struct TreeNode {
    pub val: i32,
    pub left: Option<Rc<RefCell<TreeNode>>>,
    pub right: Option<Rc<RefCell<TreeNode>>>,
}
// 
impl TreeNode {
    #[inline]
    pub fn new(val: i32) -> Self {
        TreeNode {
        val,
        left: None,
        right: None
        }
    }
}

struct FlattenBinaryTreeToLinkedList (u8);

impl FlattenBinaryTreeToLinkedList {

    pub fn flatten(root: &mut Option<Rc<RefCell<TreeNode>>>) {

        let mut node = root.clone();

        while node.is_some() {

            println!("{}, ", node.as_ref().unwrap().borrow().val);

            if node.as_ref().unwrap().borrow().left.is_none() {
                let m = node.as_ref().unwrap().borrow().right.clone();
                node = m;
                continue;
            }

            let mut pre = node.as_ref().unwrap().borrow().left.clone();

            while pre.as_ref().unwrap().borrow().right.is_some() {
                let m = pre.as_ref().unwrap().borrow().right.clone();
                pre = m;
            }

            pre.as_mut().unwrap().borrow_mut().right = node.as_ref().unwrap().borrow().right.clone();
            let left_child = node.as_ref().unwrap().borrow().left.clone();
            node.as_mut().unwrap().borrow_mut().right = left_child;
            node.as_mut().unwrap().borrow_mut().left = None;
            let m = node.as_mut().unwrap().borrow_mut().right.clone();
            node = m;
        }
    }


    pub fn flatten_cur(root: &mut Option<Rc<RefCell<TreeNode>>>) {

        if let Some(node) = root {

            if node.borrow().left.is_none() && node.borrow().right.is_none() {
                return;
            }

            FlattenBinaryTreeToLinkedList::flatten_cur(&mut node.borrow_mut().left);

            FlattenBinaryTreeToLinkedList::flatten_cur(&mut node.borrow_mut().right);

            let mut n = node.clone();

            if n.borrow().left.is_none() {
                return;
            }

            let l = n.borrow().left.clone().unwrap();
            n = l;

            while ! n.borrow().right.is_none() {
                let r = n.borrow().right.clone();
                n = r.unwrap();
            }

            let left = node.borrow().left.clone();
            n.borrow_mut().right = node.borrow().right.clone();
            node.borrow_mut().right = left;
            node.borrow_mut().left = None;
        }

    }
}

pub fn test_114_Flatten_binary_tree_to_linked_list() {

    let mut root = Some(Rc::new(RefCell::new(TreeNode::new(1))));

    root.as_mut().unwrap().borrow_mut().left = Some(Rc::new(RefCell::new(TreeNode::new(2))));
    root.as_mut().unwrap().borrow_mut().right = Some(Rc::new(RefCell::new(TreeNode::new(5))));

    root.as_mut().unwrap().borrow_mut().left.as_mut().unwrap().borrow_mut().left = Some(Rc::new(RefCell::new(TreeNode::new(3))));
    root.as_mut().unwrap().borrow_mut().left.as_mut().unwrap().borrow_mut().right = Some(Rc::new(RefCell::new(TreeNode::new(4))));

    root.as_mut().unwrap().borrow_mut().right.as_mut().unwrap().borrow_mut().right = Some(Rc::new(RefCell::new(TreeNode::new(6))));

    FlattenBinaryTreeToLinkedList::flatten(&mut root);
    // FlattenBinaryTreeToLinkedList::flatten_cur(&mut root);

    while root.is_some() {

        println!("{}, ", root.as_ref().unwrap().borrow().val);

        let m = root.as_ref().unwrap().borrow().right.clone();
        root = m;
    }
}