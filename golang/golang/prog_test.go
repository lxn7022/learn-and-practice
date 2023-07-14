package golang

import (
	"fmt"
	"reflect"
	"testing"

	. "github.com/smartystreets/goconvey/convey"
)

func TestExample(t *testing.T) {
	tests := []struct {
		name string
	}{
		{"function:TestExample"},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			Example()
		})
	}
}

func TestExam1(t *testing.T) {
	tests := []struct {
		name string
	}{
		{"function:TestExam1"},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			Exam1()
		})
	}
}

func TestExam2(t *testing.T) {
	tests := []struct {
		name string
	}{
		{"function:TestExam2"},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			Exam2()
		})
	}
}

func TestExam4(t *testing.T) {
	type args struct {
		a []int
	}
	tests := []struct {
		name string
		args args
	}{
		{"function:TestExam4", args{[]int{4, 5, 6, 3, 2, 1}}},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			Exam4(tt.args.a)
			fmt.Printf("%+v\n", tt.args.a)
		})
	}
}

func TestExam3(t *testing.T) {
	tests := []struct {
		name string
	}{
		{"function:TestExam3 "},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			Exam3()
		})
	}
}

func TestBraces(t *testing.T) {
	type args struct {
		N int
	}
	tests := []struct {
		name string
		args args
	}{
		{"function:TestBraces ", args{3}},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			Braces(tt.args.N)
		})
	}
}

func TestExam5(t *testing.T) {
	tests := []struct {
		name string
	}{
		{"function:TestExam5 "},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			Exam5()
		})
	}
}

func TestExam6(t *testing.T) {
	tests := []struct {
		name string
	}{
		{"function:TestExam6 "},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			Exam6()
		})
	}
}

func TestMulti99(t *testing.T) {
	tests := []struct {
		name string
	}{
		{"function:TestMulti99 "},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			Multi99()
		})
	}
}

func TestIsHuiwen(t *testing.T) {
	type args struct {
		a string
	}
	tests := []struct {
		name string
		args args
		want bool
	}{
		{"function:IsHuiwen ", args{"121"}, true},
		{"function:IsHuiwen ", args{"1221"}, true},
		{"function:IsHuiwen ", args{"1234"}, false},
		{"function:IsHuiwen ", args{"12221"}, true},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got := IsHuiwen(tt.args.a); got != tt.want {
				t.Errorf("IsHuiwen() = %v, want %v", got, tt.want)
			}
		})
	}
}

func TestExam41(t *testing.T) {
	type args struct {
		a []string
	}
	tests := []struct {
		name string
		args args
	}{
		{"function:Exam41 ", args{[]string{"121", "a", "bb", "ab"}}},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			Exam41(tt.args.a)
		})
	}
}

func TestGetNearestCoord(t *testing.T) {
	type args struct {
		vec []Coord
		e   Coord
		k   int
	}
	tests := []struct {
		name string
		args args
		want []Coord
	}{
		{"function:GetNearestCoord ",
			args{[]Coord{{1, 2}, {3, 4}, {7, 8}}, Coord{0, 0}, 2},
			[]Coord{{1, 2}, {3, 4}}},
		{"function:GetNearestCoord ",
			args{[]Coord{{1, 2}, {3, 4}, {7, 8}}, Coord{3, 4}, 2},
			[]Coord{{3, 4}, {1, 2}}},
		{"function:GetNearestCoord ",
			args{[]Coord{{1, 2}, {3, 4}, {7, 8}}, Coord{7, 8}, 2},
			[]Coord{{7, 8}, {3, 4}}},
		{"function:GetNearestCoord ",
			args{[]Coord{{1, 2}, {3, 4}, {7, 8}}, Coord{7, 8}, 2},
			[]Coord{{1, 2}, {3, 4}}},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got := GetNearestCoord(tt.args.vec, tt.args.e, tt.args.k); !reflect.DeepEqual(got, tt.want) {
				t.Errorf("GetNearestCoord() = %v, want %v", got, tt.want)
			}
		})
	}
}

func TestLineNum(t *testing.T) {
	type args struct {
		file   []string
		substr string
	}
	tests := []struct {
		name string
		args args
		want int
	}{
		{"function:LineNum ",
			args{[]string{"mkdir1", "func mkdi", "bb", "ab"}, "mk"}, 2},
		{"function:LineNum ",
			args{[]string{"mkdir1", "func mkdi", "bb", "ab"}, "mkdir"}, 1},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got := LineNum(tt.args.file, tt.args.substr); got != tt.want {
				t.Errorf("LineNum() = %v, want %v", got, tt.want)
			}
		})
	}
}

func TestStatTimes(t *testing.T) {
	type args struct {
		arr []int32
		cnt int32
	}
	tests := []struct {
		name string
		args args
		want []int32
	}{
		{"function:StatTimes ",
			args{[]int32{100, 123, 123, 123, 123, 123, 455, 876}, 3}, []int32{123}},
		{"function:StatTimes ",
			args{[]int32{100, 100, 123, 123, 123, 123, 123, 455, 876}, 1}, []int32{100, 123}},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got := StatTimes(tt.args.arr, tt.args.cnt); !reflect.DeepEqual(got, tt.want) {
				t.Errorf("StatTimes() = %v, want %v", got, tt.want)
			}
		})
	}
}

func TestDB(t *testing.T) {
	Convey("Staff", t, func() {

		staff := Staff{}
		staff.Init("")

		t.Logf("%v", staff.GetMemberInfo("lark"))
		t.Logf("%s", staff.GetMembersOfCenter(101))
		t.Logf("%s", staff.GetMembersOfCenter(102))
		t.Logf("%s", staff.GetMembersOfDepart(10))
		t.Logf("%s", staff.GetMembersOfDepart(11))

	})

}

func TestGetTopStarUser(t *testing.T) {
	type args struct {
		flows []Record
		n     int32
	}
	tests := []struct {
		name        string
		args        args
		wantTopStar []string
		wantTopUser []string
	}{
		// TODO: Add test cases.
		{"function:GetTopStarUser ",
			args{[]Record{{"UserID1", "StarID1"}, {"UserID1", "StarID2"}, {"UserID1", "StarID2"}, {"UserID2", "StarID2"}, {"UserID3", "StarID2"}}, 10},
			[]string{}, []string{}},
		{"function:GetTopStarUser ",
			args{[]Record{{"UserID1", "StarID1"}, {"UserID1", "StarID2"}, {"UserID3", "StarID5"}, {"UserID4", "StarID3"}}, 10},
			[]string{}, []string{}},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			gotTopStar, gotTopUser := GetTopStarUser(tt.args.flows, tt.args.n)
			if !reflect.DeepEqual(gotTopStar, tt.wantTopStar) {
				t.Errorf("GetTopStarUser() gotTopStar = %v, want %v", gotTopStar, tt.wantTopStar)
			}
			if !reflect.DeepEqual(gotTopUser, tt.wantTopUser) {
				t.Errorf("GetTopStarUser() gotTopUser = %v, want %v", gotTopUser, tt.wantTopUser)
			}
		})
	}
}

func TestRightViewOfBiTree(t *testing.T) {
	Convey("TestRightViewOfBiTree\n", t, func() {

		node8 := BiTreeNode{8, nil, nil}
		node12 := BiTreeNode{12, nil, nil}
		node10 := BiTreeNode{10, &node8, &node12}
		root := BiTreeNode{15, &node10, nil}

		RightViewOfBiTree(&root)

	})

}

func Test_twoSumHash(t *testing.T) {
	type args struct {
		nums   []int
		target int
	}
	tests := []struct {
		name string
		args args
		want []int
	}{
		// TODO: Add test cases.
		{"function:GetTopStarUser ",
			args{[]int{1, 2, 3, 4, 5, 6}, 10}, []int{3, 5}},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got := twoSumHash(tt.args.nums, tt.args.target); !reflect.DeepEqual(got, tt.want) {
				t.Errorf("twoSumHash() = %v, want %v", got, tt.want)
			}
		})
	}
}

func Test_longestPalindrome(t *testing.T) {
	type args struct {
		s string
	}
	tests := []struct {
		name string
		args args
		want string
	}{
		// TODO: Add test cases.
		{"Test longestPalindrome :\n", args{"aabacccd"}, "aba"},
		{"Test longestPalindrome :\n", args{"aaabacccd"}, "aaa"},
		{"Test longestPalindrome :\n", args{"aabaccdcaxacdc"}, "cdcaxacdc"},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got := longestPalindrome(tt.args.s); got != tt.want {
				t.Errorf("longestPalindrome() = %v, want %v", got, tt.want)
			}
		})
	}
}

func Test_divide(t *testing.T) {
	type args struct {
		a int
		b int
	}
	tests := []struct {
		name string
		args args
		want int
	}{
		// TODO: Add test cases.
		{"function:divide ", args{7, -3}, -2},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got := divide(tt.args.a, tt.args.b); got != tt.want {
				t.Errorf("divide() = %v, want %v", got, tt.want)
			}
		})
	}
}

func Test_addBinary(t *testing.T) {
	type args struct {
		a string
		b string
	}
	tests := []struct {
		name string
		args args
		want string
	}{
		// TODO: Add test cases.
		{"function:divide ", args{"11", "10"}, "101"},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got := addBinary(tt.args.a, tt.args.b); got != tt.want {
				t.Errorf("addBinary() = %v, want %v", got, tt.want)
			}
		})
	}
}

func Test_TreeAncestor(t *testing.T) {
	Convey("Test_TreeAncestor", t, func() {
		n := 7
		parent := []int{-1, 0, 0, 1, 1, 2, 2}
		obj := Constructor(n, parent)
		ret := obj.GetKthAncestor(6, 3)
		So(ret, ShouldEqual, -1)
		ret = obj.GetKthAncestor(3, 1)
		So(ret, ShouldEqual, 1)
		ret = obj.GetKthAncestor(5, 2)
		So(ret, ShouldEqual, 0)
	})
}

func Test_employ(t *testing.T) {
	Convey("Test_employ", t, func() {

		ret := employ(10, 1, 2, 1, 10)
		So(ret, ShouldResemble, []int{10, 22, 66, 198, 594, 1782, 5346, 16038, 48114, 144342})

		ret = employ(10, 1, 1, 1, 10)
		So(ret, ShouldResemble, []int{})

	})
}
