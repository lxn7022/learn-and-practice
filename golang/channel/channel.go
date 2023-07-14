package channel

import (
	"fmt"
	"time"
)

func Example1() {
	c := make(chan int, 10)
	c <- 1
	c <- 2
	close(c)
	for i := range c {
		fmt.Println(i)
	}
}

func Example2() {
	c := make(chan int, 10)
	c <- 1
	c <- 2
	close(c)
	//c <- 3 panic
	fmt.Println(<-c)
	fmt.Println(<-c)
	fmt.Println(<-c)

}

func Example3() {
	type Elem struct {
		i int
	}
	ch := make(chan interface{}, 5)
	go func() {
		time.Sleep(time.Second * 1) //mock rpc1
		ch <- "result"
	}()
	go func() {
		time.Sleep(time.Second * 1) //mock rpc2
		ch <- []int{1}
	}()
	go func() {
		time.Sleep(time.Second * 1) //mock rpc3
		ch <- 1
	}()
	go func() {
		time.Sleep(time.Second * 2) //mock rpc4
		ch <- map[string]int{"alice": 18}
	}()
	go func() {
		time.Sleep(time.Second * 1) //mock rpc5
		ch <- Elem{2}
	}()

	isError := false
	for range "12345" {
		select {
		case e := <-ch:
			switch x := e.(type) {
			case string:
				fmt.Printf("func1:%+v\n", x)
			case int:
				fmt.Printf("func2:%+v\n", x)
			case []int:
				fmt.Printf("func3:%+v\n", x)
				isError = true //模拟出错
			case map[string]int:
				fmt.Printf("func4:%+v\n", x)
			case Elem:
				fmt.Printf("func5:%+v\n", x)

			}
		case <-time.After(time.Second * 3):
			fmt.Println("timeout")
		}
		if isError {
			fmt.Println("ErrorAndExit")
			break
		}
	}
}

func Example4() {

	ch := make(chan interface{}, 3)
	//mock rpc1
	type RspOfRPC1 struct {
		i int
	}
	go func() {
		time.Sleep(time.Second * 1) //mock rpc1
		ch <- RspOfRPC1{1}
	}()
	//mock rpc2
	type RspOfRPC2 struct {
		i int
	}
	go func() {
		time.Sleep(time.Second * 2) //mock rpc1
		ch <- RspOfRPC2{2}
	}()
	//mock rpc3
	type RspOfRPC3 struct {
		i int
	}
	go func() {
		time.Sleep(time.Second * 1) //mock rpc1
		ch <- RspOfRPC3{3}
	}()

	var (
		rsp1 RspOfRPC1
		rsp2 RspOfRPC2
		rsp3 RspOfRPC3
	)
	isError := false
	for range "123" {
		select {
		case e := <-ch:
			switch x := e.(type) {
			case RspOfRPC1:
				rsp1 = x
				fmt.Printf("func1:%+v\n", x)
			case RspOfRPC2:
				rsp2 = x
				fmt.Printf("func2:%+v\n", x)
			case RspOfRPC3:
				rsp3 = x
				fmt.Printf("func3:%+v\n", x)
				//isError = true //模拟出错
			}
		case <-time.After(time.Second * 3):
			fmt.Println("timeout")
		}
		if isError {
			fmt.Println("ErrorAndExit")
			break
		}

	}
	if isError {
		fmt.Printf("isError:%+v\n", isError)
		return
	}
	//rpc1 rpc2 rpc3 都成功
	fmt.Printf("sucess:%+v,%+v,%+v\n", rsp1, rsp2, rsp3)

}

func Example5() {

	timer := time.NewTimer(1 * time.Second)
	select {
	case <-timer.C:
		fmt.Println("timeout")
	}

}
