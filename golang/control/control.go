package control

import "fmt"

func Example1() {
	switch finger := 1; finger { //finger is declared in switch
	case 1:
		fmt.Println("Thumb")
	case 2:
		fmt.Println("Index")
	case 3:
		fmt.Println("Middle")
	case 4:
		fmt.Println("Ring")
	case 5:
		fmt.Println("Pinky")
	default: //default case
		fmt.Println("incorrect finger number")
	}
}

func Example2() {
	finger := 4
	switch finger { //finger is declared in switch
	case 1:
		fmt.Println("Thumb")
	case 2:
		fmt.Println("Index")
	case 3:
		fmt.Println("Middle")
	case 4:
		fmt.Println("Ring")
	case 5:
		fmt.Println("Pinky")
	default: //default case
		fmt.Println("incorrect finger number")
	}
}

func Example3() {
	num := 75
	switch { // expression is omitted
	case num >= 0 && num <= 50:
		fmt.Println("[0-50]")
	case num >= 51 && num <= 100:
		fmt.Println("[51-100]")
	case num >= 101:
		fmt.Println("[101-max]")
	}

}

func Example4() {
	letter := "i"
	switch letter {
	case "a", "e", "i", "o", "u": //multiple expressions in case
		fmt.Println("vowel")
	default:
		fmt.Println("not a vowel")
	}
}

func breakLabel() {
BREAKDEMO1:
	for i := 0; i < 10; i++ {
		for j := 0; j < 10; j++ {
			if j == 2 {
				break BREAKDEMO1
			}
			fmt.Printf("%v-%v\n", i, j)
		}
	}
	fmt.Println("...")
}

func gotoLabel() {
	for i := 0; i < 10; i++ {
		for j := 0; j < 10; j++ {
			if j == 2 {
				goto breakTag
			}
			fmt.Printf("%v-%v\n", i, j)
		}
	}
	return
breakTag:
	fmt.Println("结束for循环")
}

func continueLabel() {
forloop1:
	for i := 0; i < 5; i++ {
		// forloop2:
		for j := 0; j < 5; j++ {
			if i == 2 && j == 2 {
				continue forloop1
			}
			fmt.Printf("%v-%v\n", i, j)
		}
	}
}

func Example6() {
	ch1 := make(chan int, 1)
	ch2 := make(chan int, 1)

	ch1 <- 3
	ch2 <- 5

	for range "12" {
		select {
		case <-ch1:
			fmt.Println("ch1 selected.")
			break
		case <-ch2:
			fmt.Println("ch2 selected.")
			fmt.Println("ch2 selected without break")
		}
	}
}

func Example7() {
	m := map[string]int{
		"alice": 11,
		"bob":   12,
	}
	x := 1
	for range m {
		fmt.Println(x)
		x++
	}

	m2 := map[string]int{}
	m2["alice"] = 11
	m2["bob"] = 12
	for range m2 {
		fmt.Println(x)
		x++
	}

}

func Example8() {
	m := map[string]int{
		"alice": 11,
		"bob":   12,
	}
	x := 1
	for range m {
		fmt.Println(x)
		x++
	}

	m2 := map[string]int{}
	m2["alice"] = 11
	m2["bob"] = 12
	for range m2 {
		fmt.Println(x)
		x++
	}

}
