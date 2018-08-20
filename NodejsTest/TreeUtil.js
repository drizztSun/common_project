'use strict'



class BinaryTreeNode {

    constructor(n) {
        this._vale = n;
        this._left = null;
        this._right = null;
    }

    static isBalanced(treeNode) {
        //return BinaryTreeNode.check_balance(treeNode) > 0　
        return BinaryTreeNode.check_balance_with_height(treeNode, 0) > 0;
    }

    static check_balance(treeNode) {
        if (treeNode == null)
            return 0;

        let left = BinaryTreeNode.check_balance(treeNode._left);
        let right = BinaryTreeNode.check_balance(treeNode._right);
    
        if (left == -1 || right == -1 || Math.abs(left - right) > 1) {
            return -1;
        }

        return Math.max(left + 1, right + 1);
    }

    static check_balance_with_height(treeNode, height) {
        if (treeNode == null)
            return height;

        let left = BinaryTreeNode.check_balance_with_height(treeNode._left, height + 1);
        let right = BinaryTreeNode.check_balance_with_height(treeNode._right, height + 1);

        if (left == -1 || right == -1 || Math.abs(left - right) > 1) {
            return -1;
        }
        return Math.max(left, right);
    }

}

// Get the common parent node for two nodes in a tree
// Common way NO 1, O(n^2)
function IsChildNode()
{


}


function main() {

    let root = new BinaryTreeNode(1);
    root._left = new BinaryTreeNode(2);
    root._right = new BinaryTreeNode(3);

    root._left._left = new BinaryTreeNode(4);
    root._left._left._left = new BinaryTreeNode(5);

    console.log("Tree balanced is " + BinaryTreeNode.isBalanced(root));
}

exports.main = main;

