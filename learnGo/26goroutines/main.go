// ============================================================================
// ============================================================================
// Go routines:
// ------------
//  0. Go routines are lightweight threads of execution. They are managed by the
//     Go runtime.
//  1. They are used to run functions concurrently. They are started using the
//     keyword "go" followed by the function call.
//  2. In order to wait for a go routine to finish, we can use the sync.WaitGroup
//    type. In this example, there are two go routines that are started, and we
//    wait for them to finish using the WaitGroup.
//  3. The WaitGroup variable is eventually used to have the main function
//     which is also a goroutine, wait for the go routines to finish.
//
// ============================================================================
// ============================================================================
package main

import (
	"fmt"
	"sync"
)

func main() {
	fmt.Println("start of main program for goroutines examples")

	// 2)
	var wg sync.WaitGroup
	wg.Add(2)

	// 1)
	go greeter("hello", &wg)
	go greeter("world", &wg)

	// 3)
	wg.Wait()
}

func greeter(s string, wg *sync.WaitGroup) {
	defer wg.Done()
	for i := 0; i < 3; i++ {
		fmt.Println(s)
	}
}
