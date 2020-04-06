package leetcodeH

/*
1028. Recover a Tree From Preorder Traversal

We run a preorder depth first search on the root of a binary tree.

At each node in this traversal, we output D dashes (where D is the depth of this node), then we output the value of this node.
(If the depth of a node is D, the depth of its immediate child is D+1.  The depth of the root node is 0.)

If a node has only one child, that child is guaranteed to be the left child.

Given the output S of this traversal, recover the tree and return its root.



Example 1:

Input: "1-2--3--4-5--6--7"
Output: [1,2,5,3,4,6,7]

Example 2:

Input: "1-2--3---4-5--6---7"
Output: [1,2,5,3,null,6,null,4,null,7]

Example 3:

Input: "1-401--349---90--88"
Output: [1,401,null,349,88,90]

*/

func recoverFromPreorder(S string) *TreeNode {

	groups := make(map[int][]*TreeNode)
	level := 0
	base := 0

	for i := 0; i < len(S); i++ {

		if S[i] == '-' {
			level++
			continue
		}

		base = base*10 + int(S[i]-'0')
		if i+1 == len(S) || S[i+1] == '-' {
			if _, ok := groups[level]; !ok {
				groups[level] = make([]*TreeNode, 0)
			}
			n := TreeNode{Val: base}
			if level-1 > -1 {
				if v, ok := groups[level-1]; ok {
					if v[len(v)-1].Left == nil {
						v[len(v)-1].Left = &n
					} else if v[len(v)-1].Right == nil {
						v[len(v)-1].Right = &n
					}
				}
			}
			groups[level] = append(groups[level], &n)

			base = 0
			level = 0
		}

	}

	return groups[0][0]
}

func Test_1028_RecoverATreeFromPreorderTraversal() {

	recoverFromPreorder("1-2--3--4-5--6--7")

	recoverFromPreorder("1-2--3---4-5--6---7")

	recoverFromPreorder("1-401--349---90--88")
}
