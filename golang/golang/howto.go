package golang

import (
	"fmt"
	"sort"
)

// Example1 map
func Example1() {
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

// Example2 map
func Example2() {
	m := map[string]int{
		"x": 4,
		"a": 1,
		"b": 2,
		"d": 3,
	}
	if v, ok := m["x"]; ok {
		fmt.Printf("v:%+v\n", v)
	} else {
		fmt.Printf("不存在\n")
	}

}

// Example3 map
// go的map是hashmap，所以读取遍历的顺序是不保证的，如果业务需要保证key的遍历顺序，建议将key单独保存到一个slice里
func Example3() {
	m := map[string]int{
		"x": 4,
		"a": 1,
		"b": 2,
		"d": 3,
	}
	for k, v := range m {
		fmt.Println("Key:", k, "Value:", v)
	}
	keys := []string{}
	for k := range m {
		keys = append(keys, k)
	}
	sort.Strings(keys)
	for _, k := range keys {
		fmt.Println("Key:", k, "Value:", m[k])
	}
}

func Example4() {
	nums := []int{}
	for i := 0; i < 10; i++ {
		nums = append(nums, i)
	}
	fmt.Printf("nums:%+v\n", nums)
}

// Example5 ...
func Example5() {
	f := func(a, b int) int {
		return a + b
	}
	fmt.Printf("f(1,2):%+v\n", f(1, 2))
}

// Circle ...
type Circle struct {
	x      int
	y      int
	Radius int
}

// Example6 ...
func Example6() {
	c := Circle{100, 100, 123}
	fmt.Printf("Circle:%+v\n", c)
}

type result struct {
	IP    string  `json:"IP"`
	Value float64 `json:"Value"`
}

type byValue []result

func (v byValue) Len() int {
	return len(v)
}

func (v byValue) Swap(i, j int) {
	v[i], v[j] = v[j], v[i]
}

func (v byValue) Less(i, j int) bool {
	return v[i].Value < v[j].Value
}

func Example7() {
	reList := []result{}
	reList = append(reList, result{"0.0.0.1", 1.0})
	reList = append(reList, result{"0.0.0.2", 2.0})
	reList = append(reList, result{"0.0.0.3", 3.0})
	sort.Sort(byValue(reList))
	fmt.Printf("Circle:%+v\n", reList)
}

func Example8() {
	reList := []result{}
	reList = append(reList, result{"0.0.0.1", 1.0})
	reList = append(reList, result{"0.0.0.2", 2.0})
	reList = append(reList, result{"0.0.0.3", 3.0})
	sort.Slice(reList, func(i, j int) bool {
		return reList[i].Value < reList[j].Value

	})
	fmt.Printf("Circle:%+v\n", reList)
}
