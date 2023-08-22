package problem

import (
	"testing"

	. "github.com/smartystreets/goconvey/convey"
)

func Test_PreorderTraversal(t *testing.T) {
	Convey("Test_PreorderTraversal", t, func() {

		node8 := TreeNode{8, nil, nil}
		node12 := TreeNode{12, nil, nil}
		node10 := TreeNode{10, &node8, &node12}
		root := TreeNode{15, &node10, nil}

		ans := PreorderTraversal(&root)
		So(ans, ShouldResemble, []int{15, 10, 8, 12})

	})
}
