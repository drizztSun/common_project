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

    //use std::rc::Rc;
    //use std::cell::RefCell; 
    //use parent::TreeNode;

    pub fn flatten(root: &mut Option<Rc<RefCell<TreeNode>>>) {
        /*
        while root.is_some() {

            if root.as_mut().left.is_none() {
                root = root.as_mut().right;
                continue;
            }

            let mut pre: Option<Rc<RefCell<TreeNode>>> = Rc::clone(root.as_mut().left);
            while pre.right.is_some() {

            }

        }
         */
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

        }

    }
}

pub fn test_114_Flatten_binary_tree_to_linked_list() {

    let root = Rc::new(RefCell::new(TreeNode::new(1)));

    root.borrow_mut().left = Some(Rc::new(RefCell::new(TreeNode::new(2))));
    root.borrow_mut().right = Some(Rc::new(RefCell::new(TreeNode::new(5))));

    root.borrow_mut().left.as_mut().unwrap().borrow_mut().left = Some(Rc::new(RefCell::new(TreeNode::new(3))));
    root.borrow_mut().left.as_mut().unwrap().borrow_mut().right = Some(Rc::new(RefCell::new(TreeNode::new(4))));

    root.borrow_mut().right.as_mut().unwrap().borrow_mut().right = Some(Rc::new(RefCell::new(TreeNode::new(6))));

    FlattenBinaryTreeToLinkedList::flatten(&mut Some(root));
}