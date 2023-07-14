package context

import (
	"context"
	"fmt"
	"time"
)

func Example1() {
	messages := make(chan int, 10)
	defer close(messages)

	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()

	// producer
	for i := 0; i < 10; i++ {
		messages <- i
	}

	// consumer
	go func(ctx context.Context) {
		ticker := time.NewTicker(1 * time.Second)
		for range ticker.C {
			select {
			case <-ctx.Done():
				fmt.Println("child process interrupt...")
				return
			case m := <-messages:
				fmt.Printf("send message: %d\n", m)
			}
		}
	}(ctx)

	select {
	case <-ctx.Done():
		time.Sleep(1 * time.Second)
		fmt.Println("main process exit!")
	}
}
