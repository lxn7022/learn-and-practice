package golang

import (
	"fmt"
	"math"
	"sort"
	"strconv"
	"strings"
	"time"
)

// Example map
func Example() {
	m := map[string]int{
		"a": 1,
		"b": 2,
	}
	m["c"] = 3
	m["d"] = 4
	for k, v := range m {
		fmt.Printf("k:[%v].v:[%v]\n", k, v) // 输出k,v值
	}

	delete(m, "a")
	for k, v := range m {
		fmt.Printf("k:[%v].v:[%v]\n", k, v) // 输出k,v值
	}
}

// Exam1 ...
func Exam1() {
	priceList := []int{100, 80, 120, 130, 70, 60, 100, 125}
	benefit := 0
	for i := 0; i < len(priceList)-1; i++ {
		for j := i; j < len(priceList); j++ {
			in := priceList[i]
			out := priceList[j]
			if out-in > benefit {
				benefit = out - in
			}
		}
	}
	fmt.Printf("max benefit: %+v\n", benefit)

}

// Exam2 ...
func Exam2() {
	priceList := []int{100, 80, 120, 130, 70, 60, 100, 125}
	benefit := 0
	for i := 0; i < len(priceList)-1; i++ {
		for j := i; j < len(priceList); j++ {
			in := priceList[i]
			out := priceList[j]
			tmp := out - in
			if tmp > 0 {
				benefit += tmp
				i = j + 1
				break
			}
		}
	}
	fmt.Printf("max benefit: %+v\n", benefit)

}

// Judge ...
func Judge(s string) {

	stack := []byte{}
	lenStack := 0
	for i := 0; i < len(s); i++ {
		ch := s[i]
		if ch == '(' {
			// 左括号入栈
			stack = append(stack, ch)

		} else if ch == ')' {
			// 右括号和栈顶比较
			lenStack = len(stack)
			if stack[lenStack-1] == '(' {
				stack = stack[:lenStack-1]
			}
		}
	}
	lenStack = len(stack)
	if lenStack == 0 {
		fmt.Printf("this is a valid string\n")
	} else {
		fmt.Printf("this is a invalid string\n")
	}
	fmt.Printf("%+v\n", stack)
}

// Exam3 ...
func Exam3() {
	input1 := "((()))()()()"
	input2 := "((()))()(((("
	Judge(input1)
	Judge(input2)

}

// Exam4 整数数组排序
func Exam4(a []int) {
	sort.Ints(a)
}

// Exam41 字符串数组排序
func Exam41(a []string) {
	fmt.Printf("input string: %v\n", a)
	sort.Strings(a)
	fmt.Printf("input string: %v\n", a)
}

// BracesHelper ...
func BracesHelper(left, right, cur, size int, output []string) {
	if size == right {
		fmt.Printf("%+v\n", output)
		return
	}
	for i := cur; i < size; i++ {
		output = append(output, "( ")
		left++
		if left < size {
			BracesHelper(left, right, i+1, size, output)
		}
		if left >= right {
			output = append(output, ") ")
			right++
			BracesHelper(left, right, i+1, size, output)
		}
	}
}

// Braces ...
func Braces(N int) {
	output := []string{}
	BracesHelper(0, 0, 0, N, output)
}

// MatchBrackets ...
func MatchBrackets(bracketsNum int, nLen int, brackets []string) {
	left := 0
	right := 0
	for i := 0; i < len(brackets); i++ {
		if brackets[i] == "(" {
			left++
		} else {
			right++
		}
		if right > left {
			return
		}
		if left == right && left+right == bracketsNum {
			fmt.Printf("%+v\n", brackets)
		}
	}

	if nLen > 0 {
		brackets = append(brackets, "(")
		MatchBrackets(bracketsNum, nLen-1, brackets)
		brackets = brackets[:len(brackets)-1]

		brackets = append(brackets, ")")
		MatchBrackets(bracketsNum, nLen-1, brackets)
		brackets = brackets[:len(brackets)-1]
	}
}

// Exam5 ...
func Exam5() {
	output := []string{}
	N := 6 //必须是偶数
	MatchBrackets(N, N, output)
}

// SUM ...
var SUM int = 0

func arrayCount(firstCount, secondCount, number, N int, brackets []string) {
	if firstCount < secondCount || number < 0 || firstCount > N/2 || secondCount > N/2 {
		return
	}

	if firstCount == N/2 && secondCount == N/2 && number == 0 {
		SUM++
		fmt.Printf("%+v\n", brackets)
	}

	brackets = append(brackets, "(")
	firstCount++
	arrayCount(firstCount, secondCount, number-1, N, brackets)
	brackets = brackets[:len(brackets)-1]
	firstCount--
	brackets = append(brackets, ")")
	secondCount++
	arrayCount(firstCount, secondCount, number-1, N, brackets)
	brackets = brackets[:len(brackets)-1]
	secondCount-- //最后这两行不能忘记，否则会使得arrayList无故的变大
}

// Exam6 ...
func Exam6() {
	output := []string{}
	arrayCount(0, 0, 8, 8, output)
}

// Multi99 99乘法表
func Multi99() {
	start := time.Now()
	for i := 0; i < 9; i++ {
		for j := 0; j < 9; j++ {
			fmt.Printf("%d * %d = %d", i, j, i*j)
		}
		fmt.Println()

	}
	fmt.Printf("time spend: %v", time.Since(start))

}

// IsHuiwen 回文判断
func IsHuiwen(a string) bool {

	for i := 0; i < len(a)/2; i++ {
		if a[i] == a[len(a)-1-i] {
			continue
		} else {
			return false
		}
	}
	return true
}

// ---------------------------------------------------

// Coord 坐标点
type Coord struct {
	x int32
	y int32
}

// Coordx 坐标点
type Coordx struct {
	i   int   //idx
	dis int32 // 与e点的距离
}

// SortCoordx 坐标点数组
type SortCoordx []Coordx

func (s SortCoordx) Len() int {

	return len(s)

}

func (s SortCoordx) Swap(i, j int) {

	s[i], s[j] = s[j], s[i]

}

func (s SortCoordx) Less(i, j int) bool {

	return s[i].dis < s[j].dis

}

// GetNearestCoord 获取最近的k个坐标
func GetNearestCoord(vec []Coord, e Coord, k int) []Coord {
	coordx := SortCoordx{}
	for i, c := range vec {
		distance := (c.x-e.x)*(c.x-e.x) + (c.y-e.y)*(c.y-e.y)
		coordx = append(coordx, Coordx{i, distance})

	}
	fmt.Printf("coordx before sort:%v \n", coordx)
	sort.Sort(coordx)
	fmt.Printf("coordx after sort:%v \n", coordx)
	cords := []Coord{}
	for i := 0; i < k; i++ {
		cords = append(cords, vec[coordx[i].i])
	}
	fmt.Printf("GetNearestCoordJ:%v", cords)
	return cords
}

// ---------------------------------------------------

// LineNum 统计代码行数
func LineNum(file []string, substr string) int {
	lineNum := 0
	for _, line := range file {
		if strings.Contains(line, substr) {
			lineNum++
		}
	}
	return lineNum
}

// StatTimes 如何在海量数据中找到重复次数大于某个阀值的数据？
func StatTimes(arr []int32, cnt int32) []int32 {
	numCntMap := map[int32]int32{}
	for _, num := range arr {
		if _, ok := numCntMap[num]; ok {
			numCntMap[num] = numCntMap[num] + 1
		} else {
			numCntMap[num] = 1
		}
	}

	numArr := []int32{}
	for key, val := range numCntMap {
		if val > cnt {
			numArr = append(numArr, key)
		}
	}
	return numArr
}

// --------------------------------------

// Member 员工信息
type Member struct {
	//员工英文名称、部门id、中心id
	name      string
	deptID    int32
	centertID int32
}

// Staff 结构定义
type Staff struct {

	// 员工英文名 -> 员工英详细详细
	mapMemberInfo      map[string]Member
	mapDepartToMembers map[int32][]Member
	mapCenterToMembers map[int32][]Member
}

// Init 初始化函数
func (staff *Staff) Init(filename string) error {
	// 请面试人实现该函数体
	filelines := []string{"moon 10 101", "lark 11 101", "chris 10 102", "label 15 108"}
	// 初始化map
	staff.mapMemberInfo = make(map[string]Member)
	staff.mapDepartToMembers = make(map[int32][]Member)
	staff.mapCenterToMembers = make(map[int32][]Member)

	for _, line := range filelines {
		elems := strings.Split(line, " ")
		name := elems[0]
		deptID, err := strconv.ParseInt(elems[1], 10, 64)
		if err != nil {
			return err
		}
		centerID, err := strconv.ParseInt(elems[2], 10, 64)
		if err != nil {
			return err
		}

		member := Member{name, int32(deptID), int32(centerID)}

		staff.mapMemberInfo[name] = member
		//填充mapDepartToMembers
		if members, ok := staff.mapDepartToMembers[int32(deptID)]; ok {
			members = append(members, member)
		} else {
			staff.mapDepartToMembers[int32(deptID)] = []Member{member}
		}
		//填充mapCenterToMembers
		if members, ok := staff.mapCenterToMembers[int32(centerID)]; ok {
			members = append(members, member)
		} else {
			staff.mapCenterToMembers[int32(centerID)] = []Member{member}
		}

	}
	return nil
}

// GetMemberInfo 根据员工英文名获取员工所在的部门ID和中心ID
func (staff *Staff) GetMemberInfo(name string) *Member {
	// 请面试人实现该函数体，时间复杂度O(1)
	if memInfo, ok := staff.mapMemberInfo[name]; ok {
		return &memInfo
	}
	return nil
}

// GetMembersOfDepart 获取某部门下的所有员工名
func (staff *Staff) GetMembersOfDepart(deptID int32) []string {
	// 请面试人实现该函数体，时间复杂度O(1)
	names := []string{}
	for _, member := range staff.mapDepartToMembers[deptID] {
		names = append(names, member.name)
	}
	return names
}

// GetMembersOfCenter 获取某中心下的所有员工名
func (staff *Staff) GetMembersOfCenter(centertID int32) []string {
	// 请面试人实现该函数体，时间复杂度O(1)
	names := []string{}
	for _, member := range staff.mapCenterToMembers[centertID] {
		names = append(names, member.name)
	}
	return names
}

// --------------------------------------

// Record 点赞记录
type Record struct {
	UserID string //点赞的用户的账号
	StarID string //被点赞明星的账号
}

// GetTopStarUser 请根据流水记录找出：点赞最多的N个用户，以及被点赞最多的明星ID
func GetTopStarUser(flows []Record, n int32) (topStar, topUser []string) {
	topStarMap := map[string]int{}
	topUserMap := map[string]int{}

	for _, record := range flows {

		if _, ok := topUserMap[record.UserID]; ok {
			topUserMap[record.UserID]++
		} else {
			topUserMap[record.UserID] = 1
		}

		if _, ok := topStarMap[record.StarID]; ok {
			topStarMap[record.StarID]++
		} else {
			topStarMap[record.StarID] = 1
		}

	}
	//
	topStarCntMap := map[int][]string{}
	topStarCnt := []int{}
	for starID, starCnt := range topStarMap {
		topStarCntMap[starCnt] = append(topStarCntMap[starCnt], starID)
	}
	for k, _ := range topStarCntMap {
		topStarCnt = append(topStarCnt, k)
	}
	sort.Ints(topStarCnt)
	topStar = topStarCntMap[topStarCnt[len(topStarCnt)-1]]

	//
	topUserCntMap := map[int][]string{}
	topUserCnt := []int{}
	for userID, userCnt := range topUserMap {
		topUserCntMap[userCnt] = append(topUserCntMap[userCnt], userID)
		topUserCnt = append(topUserCnt, userCnt)
	}

	for k, _ := range topUserCntMap {
		topUserCnt = append(topUserCnt, k)
	}
	sort.Ints(topUserCnt)
	for i, _ := range topUserCnt {
		topUser = append(topUser, topUserCntMap[len(topUserCnt)-i-1]...)
		if int32(len(topUser)) >= n {
			topUser = topUser[:n]
		}
	}

	fmt.Printf("%v,%v\n", topStarMap, topUserMap)
	fmt.Printf("%v,%v\n", topStar, topUser)
	return topStar, topUser
}

// --------------------------------------

// BiTreeNode 二叉树节点定义
type BiTreeNode struct {
	data  int
	left  *BiTreeNode
	right *BiTreeNode
}

// RightViewOfBiTree  打印二叉树的每一层最后侧的节点
func RightViewOfBiTree(root *BiTreeNode) {
	if root == nil {
		return
	}

	queue := []*BiTreeNode{}
	queue = append(queue, root)
	for len(queue) != 0 {
		qsize := len(queue)
		for i := 0; i < qsize; i++ {
			pnode := queue[0]
			queue = queue[1:] //从对头弹出
			// 打印最右侧节点
			if i == qsize-1 {
				fmt.Printf("RightNodeData:%v\n", pnode.data)
			}
			// 左侧节点入队列
			if pnode.left != nil {
				queue = append(queue, pnode.left)
			}
			// 右侧节点入队列
			if pnode.right != nil {
				queue = append(queue, pnode.right)
			}
		}
	}
}

// --------------------------------------
// twoSumLLoop 找出两数之和等于target，输出对应的下标
func twoSumLLoop(nums []int, target int) []int {
	for i := 0; i < len(nums); i++ {
		for j := i + 1; j < len(nums); j++ {
			if nums[i]+nums[j] == target {
				return []int{i, j}
			}
		}
	}
	return nil
}

func twoSumHash(nums []int, target int) []int {
	// 记录遍历过的数据
	hashmap := map[int]int{}
	for i := 0; i < len(nums); i++ {
		x := nums[i]
		if j, ok := hashmap[target-x]; ok {
			return []int{j, i}
		}
		hashmap[x] = i
	}
	return nil
}

// --------------------------------------

// NumNode 链表节点
type NumNode struct {
	data int
	next *NumNode
}

func addTwoNum(list1, list2 *NumNode) *NumNode {
	//  链表转为数组
	list2slice := func(list *NumNode) []int {
		numSlice := []int{}
		p := list
		for p != nil {
			numSlice = append(numSlice, p.data)
			p = p.next
		}
		return numSlice
	}
	slice2list := func(nums []int) *NumNode {
		if len(nums) == 0 {
			return nil
		}
		head := &NumNode{nums[0], nil}
		ptr := head
		for i := 1; i < len(nums); i++ {
			tmpNode := &NumNode{nums[i], nil}
			ptr.next = tmpNode
			ptr = tmpNode
		}
		return head
	}

	numSlice1 := list2slice(list1)
	numSlice2 := list2slice(list2)
	//  填充为等长数组
	padSlice := func(numSlice []int, padLen int) []int {
		padSlice := []int{}
		for i := 0; i < padLen; i++ {
			padSlice = append(padSlice, 0)
		}
		numSlice = append(numSlice, padSlice...)
		return numSlice
	}
	padLen := 0
	if len(numSlice1) > len(numSlice2) {
		padLen = len(numSlice1) - len(numSlice2)
		numSlice2 = padSlice(numSlice2, padLen)
	} else if len(numSlice1) < len(numSlice2) {
		padLen = len(numSlice2) - len(numSlice1)
		numSlice1 = padSlice(numSlice1, padLen)
	}
	// 求和
	numSlice3 := []int{}
	flag := 0
	for i := 0; i < len(numSlice1); i++ {
		sum := numSlice1[i] + numSlice2[i] + flag
		numSlice3 = append(numSlice3, sum%10)
		flag = sum / 10
	}
	if flag != 0 {
		//增加进位
		numSlice3 = append(numSlice3, flag)
	}
	// 转为list后返回
	return slice2list(numSlice3)

}

// --------------------------------------
func lengthOfLongestSubstring(s string) int {
	// 记录一个字符是否出现过，用来保证子串不重复
	m := map[byte]int{}
	strlen := len(s)

	rindex := 0
	maxlen := 0
	for i := 0; i < strlen; i++ {
		// 每前移一位，删除一个字符
		if i != 0 {
			delete(m, s[i-1])
		}
		//不断迁移右指针
		for rindex < strlen && m[s[rindex]] == 0 {
			m[s[rindex]] = 1
			rindex++
		}
		maxlen = max(maxlen, rindex-i)
		//右指针已到最右边，提前结束
		if rindex == strlen {
			break
		}
	}

	return maxlen
}

func max(x, y int) int {
	if x > y {
		return x
	}
	return y
}

// longestPalindrome 寻找最长回文子串
func longestPalindrome(s string) string {
	if len(s) == 0 {
		return ""
	}
	begin, end := 0, 0
	for i := 0; i < len(s); i++ {
		left1, right1 := expand(s, i, i)
		left2, right2 := expand(s, i, i+1)
		if right1-left1 > end-begin {
			begin, end = left1, right1
		}
		if right2-left2 > end-begin {
			begin, end = left2, right2
		}
	}
	return s[begin : end+1]

}

func expand(s string, left int, right int) (int, int) {

	for left >= 0 && right < len(s) && s[left] == s[right] {
		left, right = left-1, right+1
	}
	return left + 1, right - 1 //注意这里要回退一步
}

// divide 给定两个整数 a 和 b ，求它们的除法的商 a/b ，要求不得使用乘号 '*'、除号 '/' 以及求余符号 '%' 。
func divide(a int, b int) int {
	// err
	if b == 0 {
		return 0 //这里应该返回err
	}
	fmt.Printf("math.MinInt32:%v\n", math.MinInt32)
	// 溢出
	if a == math.MinInt32 && b == -1 {
		return math.MaxInt32
	}
	if a == math.MinInt32 && b == 1 {
		return math.MaxInt32
	}

	// 符号位
	sign := a > 0 && b < 0 || a < 0 && b > 0
	// 都转成整数，已处理越界
	if a < 0 {
		a = -a
	}
	if b < 0 {
		b = -b
	}
	div := 0
	for a >= b {
		tmpb := b
		count := 1
		for tmpb <= math.MaxInt32<<1 && a >= tmpb+tmpb {
			tmpb += tmpb
			count += count
		}
		a -= tmpb
		div += count
	}

	if sign {
		return -div
	}
	return div
}

func addBinary(a string, b string) string {

	ans := ""
	lenA := len(a)
	lenB := len(b)
	lenMax := max(lenA, lenB)

	carry := 0
	for i := 0; i < lenMax; i++ {
		if i < lenA {
			carry += int(a[lenA-1-i] - '0')
		}
		if i < lenB {
			carry += int(b[lenB-1-i] - '0')
		}
		fmt.Printf("carry:%v\n", carry)
		ans = strconv.Itoa(carry%2) + ans
		carry /= 2
	}
	if carry > 0 {
		ans = "1" + ans
	}

	return ans

}

// ListNode Definition for singly-linked list.
type ListNode struct {
	Val  int
	Next *ListNode
}

func addTwoNumbers(l1 *ListNode, l2 *ListNode) *ListNode {
	head := &ListNode{0, nil}
	cur := head

	carry := 0
	for l1 != nil || l2 != nil {
		x := ifThenElse(l1 != nil, l1.Val, 0)
		y := ifThenElse(l2 != nil, l2.Val, 0)
		sum := x + y + carry

		carry, sum = sum/10, sum%10

		cur.Next = &ListNode{sum, nil}
		cur = cur.Next

		if l1 != nil {
			l1 = l1.Next
		}
		if l2 != nil {
			l2 = l2.Next
		}
	}

	return head.Next

}

func ifThenElse(cond bool, a, b int) int {
	if cond {
		return a
	}
	return b
}

/*********************************************/

// Klog 50000< 2**16 = 65536, 50000个节点树的最大深度是16
const Klog = 16

// TreeAncestor 祖先树
type TreeAncestor struct {
	ancestors [][]int
}

// Constructor 用动态规划构建祖先树
func Constructor(n int, parent []int) TreeAncestor {
	var this TreeAncestor
	//初始化二维数组
	this.ancestors = make([][]int, n) //第1维
	for i := 0; i < n; i++ {
		this.ancestors[i] = make([]int, Klog) //第2维
		for j := 0; j < Klog; j++ {
			this.ancestors[i][j] = -1
		}
		this.ancestors[i][0] = parent[i] //根据定义ancestors[i][0]=parent[i]
	}
	//建立转移方程,按列进行
	for j := 1; j < Klog; j++ {
		for i := 0; i < n; i++ {
			firstStep := this.ancestors[i][j-1]
			if firstStep != -1 {
				secondStep := this.ancestors[firstStep][j-1]
				this.ancestors[i][j] = secondStep
			}
		}
	}
	return this
}

// GetKthAncestor 查找第K个祖先
func (t *TreeAncestor) GetKthAncestor(node, k int) int {
	for j := 0; j < Klog; j++ {
		if (k>>j)&1 != 0 {
			node = t.ancestors[node][j]
			if node == -1 {
				return -1
			}
		}
	}
	return node
}

/*
**********************************************
题目1 财主挖金币
一财主有一个金矿，在D天后该金矿会被收归国有。

财主目前有P个长工，每个长工每天可以挖G块金子。

财主每天早上可以新雇佣若干长工，每个长工需一次性支付K块金子，雇佣当天即可产出G块金子

目前财主手上有M块金子，为了在D天内获得最多金子，请问该财主需要每天新增多少长工。

func employ(D, P, G, K, M int) []int{

// 返回值：每天需新雇佣的长工数

}
**********************************************
*/
func employ(D, P, G, K, M int) []int {
	if K >= G {
		// 投入大于等于产出，无需增加人
		return []int{}
	}
	employEveryday := []int{}
	leftGold := M
	employNum := P
	for i := 0; i < D; i++ {
		incNum := leftGold / K
		employEveryday = append(employEveryday, incNum)
		employNum = employNum + incNum
		leftGold = employNum * G
	}
	return employEveryday
}
