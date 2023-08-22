package problem

// Definition for a binary tree node.
type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func PreorderTraversal(root *TreeNode) []int {

	ans := []int{}

	var preorder func(root *TreeNode)
	preorder = func(root *TreeNode) {
		if root == nil {
			return
		}

		ans = append(ans, root.Val)

		if root.Left != nil {
			preorder(root.Left)
		}
		if root.Right != nil {
			preorder(root.Right)
		}
	}
	preorder(root)
	return ans
}
